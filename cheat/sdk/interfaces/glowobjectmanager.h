#pragma once
#include "../definitions.h"
#include "../data/utlvector.h"

enum GlowRenderStyle : int
{
    GLOWRENDERSTYLE_DEFAULT = 0,
    GLOWRENDERSTYLE_RIMGLOW3D,
    GLOWRENDERSTYLE_EDGE_HIGHLIGHT,
    GLOWRENDERSTYLE_EDGE_HIGHLIGHT_PULSE,
    GLOWRENDERSTYLE_COUNT
};

class GlowObjectManager
{
public:
    struct GlowObjectDefinition
    {
        int nextFreeSlot;
        BaseEntity* entity;

        float r, g, b, a;

        bool glowAlphaCappedByRenderAlpha;
        float glowAlphaFunctionOfMaxVelocity;
        float glowAlphaMax;
        float glowPulseOverdrive;
        bool renderWhenOccluded;
        bool renderWhenUnoccluded;
        bool fullBloomRender;
        int fullBloomStencilTestValue;
        int glowStyle;
        int splitScreenSlot;

        constexpr bool IsUnused() const
        {
            return nextFreeSlot != ENTRY_IN_USE;
        }

        constexpr void SetColor(float* color)
        {
            this->r = color[0];
            this->g = color[1];
            this->b = color[2];
            this->a = color[3];

            this->renderWhenOccluded = true;
        }

        static constexpr int END_OF_FREE_LIST = -1;
        static constexpr int ENTRY_IN_USE = -2;
    };

    UtlVector<GlowObjectDefinition> glowObjectDefinitions;
    int firstFreeSlot;

    struct GlowBoxDefinition
    {
        Vector position;
        Vector orientation;
        Vector mins;
        Vector maxs;
        float birthTimeIndex;
        float terminationTimeIndex; //when to die
        Color color;
    };

    UtlVector<GlowBoxDefinition> glowBoxDefinitions;
};
