#pragma once

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

			auto player = RE::PlayerCharacter::GetSingleton();
			auto inv = player->GetInventory();
			auto settings = Settings::GetSingleton();

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
					return RE::BSEventNotifyControl::kContinue;
				}
			}
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
			if (!a_event || a_event->opening || a_event->menuName != "Loading Menu") {
				return RE::BSEventNotifyControl::kContinue;
			}

			auto settings = Settings::GetSingleton();

			if (settings->needToShowRemoveMessage) {
				settings->needToShowRemoveMessage = false;
				RE::DebugNotification(settings->TravelPackRemoveMessage.c_str(),"ITMGenericDownSD");
			}
			return RE::BSEventNotifyControl::kContinue;
		}

		static void Register()
		{
			RE::UI::GetSingleton()->AddEventSink<RE::MenuOpenCloseEvent>(OnMenuCloseHandler::GetSingleton());
		}
	};
}