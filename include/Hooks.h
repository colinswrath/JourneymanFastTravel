#pragma once

#include "FastTravelManager.h"

namespace Hooks
{
	inline static REL::Relocation<std::uintptr_t> Can_Fast_Travel_Map_Hook{ REL::ID(53095), 0x328 };

	inline bool Install() {
		return FastTravelManager::InstallCanFastTravelCheck();
	}
}