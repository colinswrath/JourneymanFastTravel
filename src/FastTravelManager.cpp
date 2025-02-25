#include "FastTravelManager.h"

#include "Hooks.h"
#include "Settings.h"
#include "Utility.h"

bool FastTravelManager::InstallCanFastTravelCheck()
{
    auto& trampoline  = SKSE::GetTrampoline();
    _CanFastTravelMap = trampoline.write_call<5>(Hooks::Can_Fast_Travel_Map_Hook.address(), CanFastTravelMap);
    logger::info("Installed ft hook");
    return true;
}

bool FastTravelManager::InstallPapyrusFastTravelCheck()
{
    auto& trampoline   = SKSE::GetTrampoline();
    _GetWorldSpaceHook = trampoline.write_call<5>(Hooks::Papyrus_Fast_Travel_Hook.address(), GetWorldSpaceHook);
    logger::info("Installed papyrus ft hook");
    return true;
}

RE::TESWorldSpace* FastTravelManager::GetWorldSpaceHook(RE::TESObjectREFR* a1)
{
    Settings::menuFastTravel = false;
    return _GetWorldSpaceHook(a1);
}

bool FastTravelManager::CanFastTravelMap(RE::Actor* a_actor, bool a_bool)
{

    auto inv      = a_actor->GetInventory();
    auto player   = RE::PlayerCharacter::GetSingleton();

    if ((!Settings::EnableOnlyOnSM || Settings::Survival_ModeEnabledShared->value == 1.0f) && !player->IsGodMode()) {

        if (Utility::IsOnFlyingMount(a_actor)) {
            return true;
        }

        for (const auto& [item, data] : inv) {
            if (!item || !item->formID) {
                continue;
            }

            if (Settings::RequiredItems->HasForm(item->GetFormID())) {

                if (_CanFastTravelMap(a_actor, a_bool)) {
                    Settings::menuFastTravel = true;
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
    else {
        return Utility::IsOnFlyingMount(a_actor) || _CanFastTravelMap(a_actor, a_bool);
    }

    // If you get to here you didnt have the required item/s and you can't travel
    RE::DebugNotification(Settings::RequiredItemNotFoundMessage.c_str());
    return false;
}
