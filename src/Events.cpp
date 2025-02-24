#include "Events.h"
#include "FastTravelManager.h"
#include "Settings.h"
#include "Utility.h"

namespace Events
{
    RE::BSEventNotifyControl FastTravelEndEventHandler::ProcessEvent(const RE::TESFastTravelEndEvent* a_event, RE::BSTEventSource<RE::TESFastTravelEndEvent>*)
    {
        if (!a_event) {
            return RE::BSEventNotifyControl::kContinue;
        }

        if (Settings::EnableOnlyOnSM == true && Settings::Survival_ModeEnabledShared->value == 0.0f) {
            Settings::menuFastTravel = false;
            return RE::BSEventNotifyControl::kContinue;
        }

        auto player = RE::PlayerCharacter::GetSingleton();
        if (Settings::menuFastTravel && !Utility::IsOnFlyingMount(player)) {
            auto inv = player->GetInventory();
            for (const auto& [item, data] : inv) {
                if (Settings::RequiredItems->HasForm(item->GetFormID())) {
                    player->RemoveItem(item, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);

                    Settings::needToShowRemoveMessage = true;
                    break;
                }
            }
        }
        Settings::menuFastTravel = false;
        return RE::BSEventNotifyControl::kContinue;
    }

    RE::BSEventNotifyControl MenuOpenCloseEventHandler::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
    {
        if (!a_event) {
            return RE::BSEventNotifyControl::kContinue;
        }

        if (Settings::EnableOnlyOnSM == true && Settings::Survival_ModeEnabledShared->value == 0.0f) {
            Settings::menuFastTravel          = false;
            Settings::needToShowRemoveMessage = false;
            return RE::BSEventNotifyControl::kContinue;
        }

        if (a_event->menuName == RE::MistMenu::MENU_NAME && !a_event->opening) {
            if (Settings::needToShowRemoveMessage) {
                Settings::needToShowRemoveMessage = false;
                RE::DebugNotification(Settings::TravelPackRemoveMessage.c_str(), "ITMGenericDownSD");
                Settings::menuFastTravel = false;
            }
        }
        else if (a_event->menuName == RE::TweenMenu::MENU_NAME && a_event->opening) {
            Settings::menuFastTravel = false;
        }
        else if (a_event->menuName == RE::CursorMenu::MENU_NAME) {
            Utility::EnableFastTravel(nullptr, nullptr, nullptr, true);
        }
        else if (a_event->menuName == RE::BookMenu::MENU_NAME) {
            Settings::menuFastTravel = false;
        }
        else if (a_event->menuName == RE::InventoryMenu::MENU_NAME) {
            Settings::menuFastTravel = false;
        }
        else if (a_event->menuName == RE::DialogueMenu::MENU_NAME) {
            Settings::menuFastTravel = false;
        }

        return RE::BSEventNotifyControl::kContinue;
    }
} // namespace Events
