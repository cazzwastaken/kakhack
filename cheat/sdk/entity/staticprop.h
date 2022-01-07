#pragma once
#include "clientunknown.h"
#include "clientrenderable.h"
#include "collideable.h"

class StaticProp : public ClientUnknown, public ClientRenderable, public Collideable, public ClientModelRenderable
{
public:
	std::byte pad0[240];
	Vector4D diffuseModulation;
};
