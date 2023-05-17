#include "FastTravelManager.h"
#include "Settings.h"
#include "Hooks.h"

bool FastTravelManager::InstallCanFastTravelCheck()
{
	auto& trampoline = SKSE::GetTrampoline();
	_CanFastTravelMap = trampoline.write_call<5>(Hooks::Can_Fast_Travel_Map_Hook.address(), CanFastTravelMap);
	logger::info("Installed ft hook");
	return true;
}

bool FastTravelManager::CanFastTravelMap(RE::Actor* a_actor, bool a_bool)
{
	auto inv = a_actor->GetInventory();
	auto settings = Settings::GetSingleton();

	for (const auto& [item, data] : inv) {
		if (settings->RequiredItems->HasForm(item->GetFormID())) {
			if (IsOnFlyingMount(a_actor) || _CanFastTravelMap(a_actor, a_bool)) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	//If you get to here you didnt have the required item/s and you can't travel
	RE::DebugNotification(settings->RequiredItemNotFoundMessage.c_str());
	return false;
}