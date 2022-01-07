#pragma once
#include <vector>

#include "../sdk/interfaces/cliententitylist.h"

class EntityListener : public ClientEntityListener
{
public:
	void Setup() noexcept;
	void Destroy() noexcept;

	void ClassCheck(BaseEntity* entity, const ClassIndex id) noexcept;
	void Update() noexcept;

	virtual void OnEntityCreated(BaseEntity* entity) override;
	virtual void OnEntityDeleted(BaseEntity* entity) override;

	std::vector<CSPlayer*> playerList = { };
};
