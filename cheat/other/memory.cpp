#include "memory.h"

#include <Windows.h>
#include <vector>
#include <stdexcept>

void m::Setup()
{
    sigs.glowObjectManager = Scan("client", "0F 11 05 ? ? ? ? 83 C8 01") + 3;
    sigs.weaponSystem = Scan("client", "8B 35 ? ? ? ? FF 10 0F B7 C0") + 2;
    sigs.viewRenderBeams = Scan("client", "B9 ? ? ? ? 0F 11 44 24 ? C7 44 24 ? ? ? ? ? F3 0F 10 84 24") + 1;
    sigs.device = Scan("shaderapidx9", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1;
    sigs.hud = Scan("client", "B9 ? ? ? ? E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? 83 C0 EC 0F 84 ? ? ? ?") + 1;
    sigs.staticPropMgr = Scan("engine", "B9 ? ? ? ? FF 50 18 8B E5") + 1;
    sigs.findElement = Scan("client", "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28 7E 1E");
    sigs.keyValuesFromString = Scan("client", "E8 ? ? ? ? 83 C4 04 89 45 D8");
    sigs.setAbsOrigin = Scan("client", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8");
    sigs.setAbsAngles = Scan("client", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8");
    sigs.startDrawing = Scan("vguimatsurface", "55 8B EC 83 E4 C0 83 EC 38");
    sigs.finishDrawing = Scan("vguimatsurface", "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ? ");
    sigs.insertIntoTree = Scan("client", "56 52 FF 50 18") + 5;
    sigs.getPlayerMoney = Scan("client", "55 8B EC 56 8B 75 08 83 FE 3F 0F 87 ? ? ? ?");
    sigs.settingsChatText = Scan("client", "55 8B EC 56 8B F1 83 BE ? ? ? ? ? 75 4B");
    sigs.showAlert = Scan("client", "55 8B EC A1 ? ? ? ? 83 EC 08 56 8B F1 57 A8 01");
    sigs.staticPropInit = Scan("engine", "53 8B DC 83 EC 08 83 E4 F8 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 8B 43 08");
    sigs.allocKeyValuesEngine = RelativeToAbsolute(reinterpret_cast<std::uintptr_t>(Scan("engine", "E8 ? ? ? ? 83 C4 08 84 C0 75 10 FF 75 0C")) + 1) + 74;
    sigs.allocKeyValuesClient = RelativeToAbsolute(reinterpret_cast<std::uintptr_t>(Scan("client", "E8 ? ? ? ? 83 C4 08 84 C0 75 10")) + 1) + 62;
    sigs.sendDatagram = Scan("engine", "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 57 8B F9 89 7C 24 18");
}

uint8_t* m::Scan(const char* module, const char* pattern)
{
    const auto handle = ::GetModuleHandle(module);

    if (!handle)
        throw std::runtime_error("Failed to get " + std::string(module) + " module handle.");

    static auto patternToByte = [](const char* pattern)
    {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?') 
            {
                ++current;

                if (*current == '?')
                    ++current;

                bytes.push_back(-1);
            }
            else
            {
                bytes.push_back(std::strtoul(current, &current, 16));
            }
        }
        return bytes;
    };


    auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(handle);
    auto ntHeaders =
        reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(handle) + dosHeader->e_lfanew);

    auto size = ntHeaders->OptionalHeader.SizeOfImage;
    auto bytes = patternToByte(pattern);
    auto scanBytes = reinterpret_cast<std::uint8_t*>(handle);

    auto s = bytes.size();
    auto d = bytes.data();

    for (auto i = 0ul; i < size - s; ++i) 
    {
        bool found = true;

        for (auto j = 0ul; j < s; ++j) 
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1) {

                found = false;
                break;
            }
        }

        if (found)
            return &scanBytes[i];
    }

    throw std::runtime_error("Outdated pattern \"" + std::string(pattern) + "\"");
}
