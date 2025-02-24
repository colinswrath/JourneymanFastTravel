#pragma once

namespace Events
{
    class FastTravelEndEventHandler final : public EventHandler<FastTravelEndEventHandler, RE::TESFastTravelEndEvent>
	{
	public:

		RE::BSEventNotifyControl ProcessEvent(const RE::TESFastTravelEndEvent* a_event, RE::BSTEventSource<RE::TESFastTravelEndEvent>*) override;
        //static void Register();
	};

    class MenuOpenCloseEventHandler final : public EventHandler<MenuOpenCloseEventHandler, RE::MenuOpenCloseEvent>
    {
    public:

        RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*) override;
    };

} // namespace Events
