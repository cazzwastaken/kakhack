#pragma once
#include "material.h"

class MaterialSystem
{
public:
    Material* CreateMaterial(const char* name, KeyValues* keyValues)
    {
        return m::Call<Material*>(this, 83, name, keyValues);
    }

    Material* FindMaterial(const char* name, const char* textureGroup = nullptr, bool complain = true, const char* complainPrefix = nullptr)
    {
        return m::Call<Material*>(this, 84, name, textureGroup, complain, complainPrefix);
    }

    short FirstMaterial()
    {
        return m::Call<short>(this, 86);
    }

    short NextMaterial(short handle)
    {
        return m::Call<short>(this, 87, handle);
    }

    short InvalidMaterial()
    {
        return m::Call<short>(this, 88);
    }

    Material* GetMaterial(short handle)
    {
        return m::Call<Material*>(this, 89, handle);
    }
};
