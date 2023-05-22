#pragma once

#include "FastTravelManager.h"

namespace Hooks
{
	inline static REL::Relocation<std::uintptr_t> Can_Fast_Travel_Map_Hook{ REL::ID(53095), 0x328 };
	inline static REL::Relocation<std::uintptr_t> Papyrus_Fast_Travel_Hook{ REL::ID(55457), 0xA1 };

	inline bool Install() {
		if (!FastTravelManager::InstallCanFastTravelCheck()) {
			return false;
		}
		if (!FastTravelManager::InstallPapyrusFastTravelCheck()) {
			return false;
		}
		return true;
	}
}