#pragma once

class FastTravelManager
{
public:
	
	static bool InstallCanFastTravelCheck();

	static bool IsOnFlyingMount(RE::Actor* a_actor)
	{
		using func_t = decltype(&FastTravelManager::IsOnFlyingMount);
		static REL::Relocation<func_t> func{ RELOCATION_ID(36877, 37901) };
		return func(a_actor);
	}

	static bool CanFastTravel(RE::Actor* a_actor, bool a_arg2)
	{
		using func_t = decltype(&FastTravelManager::CanFastTravel);
		static REL::Relocation<func_t> func{ REL::ID(40444) };
		return func(a_actor, a_arg2);
	}

protected:
	inline static bool CanFastTravelMap(RE::Actor* actor, bool a_bool);
	inline static REL::Relocation<decltype(CanFastTravelMap)> _CanFastTravelMap;
};