#include "../hooks.h"

/*
 		"SFUI_Settings_Chat_ButtonLabel" "Send"
		"SFUI_Settings_Chat_Say" "Say to all"
		"SFUI_Settings_Chat_SayTeam" "Say to team"
		"SFUI_Settings_Chat_SayParty" "Say to party"
		"SFUI_Settings_Chat_SayPartyEmpty" "Say to party (it's just you at the moment)"
		"SFUI_Settings_Chat_EnableGotv" "GOTV Chat"

		"SFUI_Settings_Chat_NotePartyChat" "[PARTY]"
		"SFUI_Settings_Chat_NotePartyInvited" "invited"
*/

void __fastcall h::SettingsChatText(void* thisptr, void* edx, const char* text)
{
	switch (fnv::Hash(text))
	{
	case fnv::HashConst("#SFUI_Settings_Chat_Say"):
		return SettingsChatTextOriginal(thisptr, "[kh] Talk kak to everyone");

	case fnv::HashConst("#SFUI_Settings_Chat_SayTeam"):
		return SettingsChatTextOriginal(thisptr, "[kh] Talk kak to your team");
	}

	SettingsChatTextOriginal(thisptr, text);
}
