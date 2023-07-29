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

bool FastTravelManager::InstallPapyrusFastTravelCheck()
{
	auto& trampoline = SKSE::GetTrampoline();
	_GetWorldSpaceHook = trampoline.write_call<5>(Hooks::Papyrus_Fast_Travel_Hook.address(), GetWorldSpaceHook);
	logger::info("Installed papyrus ft hook");
	return true;
}

RE::TESWorldSpace* FastTravelManager::GetWorldSpaceHook(RE::TESObjectREFR* a1)
{
	if (auto settings = Settings::GetSingleton()) {
		settings->menuFastTravel = false;
	}

	return _GetWorldSpaceHook(a1);
}

bool FastTravelManager::CanFastTravelMap(RE::Actor* a_actor, bool a_bool)
{
	auto inv = a_actor->GetInventory();
	auto settings = Settings::GetSingleton();
	auto player = RE::PlayerCharacter::GetSingleton();

	if ((!settings->EnableOnlyOnSM || settings->Survival_ModeEnabledShared->value == 1.0f) && !player->IsGodMode()) {
		for (const auto& [item, data] : inv) {
			if (settings->RequiredItems->HasForm(item->GetFormID())) {

				if (IsOnFlyingMount(a_actor) || _CanFastTravelMap(a_actor, a_bool)) {
					settings->menuFastTravel = true;
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
	else {
		return _CanFastTravelMap(a_actor, a_bool);
	}

	//If you get to here you didnt have the required item/s and you can't travel
	RE::DebugNotification(settings->RequiredItemNotFoundMessage.c_str());
	return false;
}
