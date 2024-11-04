#pragma once
#include "FastTravelManager.h"
#include "Settings.h"

namespace Events
{
	class OnFastTravelEndEventHandler : public RE::BSTEventSink<RE::TESFastTravelEndEvent>
	{
	public:
		static OnFastTravelEndEventHandler* GetSingleton()
		{
			static OnFastTravelEndEventHandler singleton;
			return &singleton;
		}

		RE::BSEventNotifyControl ProcessEvent(const RE::TESFastTravelEndEvent* a_event, RE::BSTEventSource<RE::TESFastTravelEndEvent>*) override
		{
			if (!a_event) {
				return RE::BSEventNotifyControl::kContinue;
			}

			auto settings = Settings::GetSingleton();
			if (settings->EnableOnlyOnSM == true && settings->Survival_ModeEnabledShared->value == 0.0f) {
				settings->menuFastTravel = false;
				return RE::BSEventNotifyControl::kContinue;
			}

			auto player = RE::PlayerCharacter::GetSingleton();
			if (settings->menuFastTravel && !FastTravelManager::IsOnFlyingMount(player)) {
				auto inv = player->GetInventory();
				for (const auto& [item, data] : inv) {
					if (settings->RequiredItems->HasForm(item->GetFormID())) {

						player->RemoveItem(
							item,
							1,
							RE::ITEM_REMOVE_REASON::kRemove,
							nullptr,
							nullptr
						);

						settings->needToShowRemoveMessage = true;
						break;
					}
				}
			}
			settings->menuFastTravel = false;
			return RE::BSEventNotifyControl::kContinue;
		}

		static void Register()
		{
			RE::ScriptEventSourceHolder* eventHolder = RE::ScriptEventSourceHolder::GetSingleton();
			eventHolder->AddEventSink(OnFastTravelEndEventHandler::GetSingleton());
		}
	};

	class OnMenuCloseHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		static OnMenuCloseHandler* GetSingleton()
		{
			static OnMenuCloseHandler singleton;
			return &singleton;
		}

		RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*) override
		{
			if (!a_event) {
				return RE::BSEventNotifyControl::kContinue;
			}

			auto settings = Settings::GetSingleton();
			if (settings->EnableOnlyOnSM == true && settings->Survival_ModeEnabledShared->value == 0.0f) {
				settings->menuFastTravel = false;
				settings->needToShowRemoveMessage = false;
				return RE::BSEventNotifyControl::kContinue;
			}

			if (a_event->menuName == RE::MistMenu::MENU_NAME && !a_event->opening) {
				if (settings->needToShowRemoveMessage) {

					settings->needToShowRemoveMessage = false;
					RE::DebugNotification(settings->TravelPackRemoveMessage.c_str(),"ITMGenericDownSD");
					settings->menuFastTravel = false;
				}
			}
			else if (a_event->menuName == RE::TweenMenu::MENU_NAME && a_event->opening) {
				settings->menuFastTravel = false;
			}
			else if (a_event->menuName == RE::CursorMenu::MENU_NAME) {
				FastTravelManager::EnableFastTravel(nullptr,nullptr,nullptr,true);
			}
			else if (a_event->menuName == RE::BookMenu::MENU_NAME) {
				settings->menuFastTravel = false;
			}
			else if (a_event->menuName == RE::InventoryMenu::MENU_NAME) {
				settings->menuFastTravel = false;
			}
			else if (a_event->menuName == RE::DialogueMenu::MENU_NAME) {
				settings->menuFastTravel = false;
			}

			return RE::BSEventNotifyControl::kContinue;
		}

		static void Register()
		{
			RE::UI::GetSingleton()->AddEventSink<RE::MenuOpenCloseEvent>(OnMenuCloseHandler::GetSingleton());
		}
	};
}
