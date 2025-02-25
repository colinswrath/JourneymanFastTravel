#pragma once

class Utility
{
public:
    static bool IsOnFlyingMount(RE::Actor* a_actor)
    {
        using func_t = decltype(&Utility::IsOnFlyingMount);
        static REL::Relocation<func_t> func{ RELOCATION_ID(36877, 37901) };
        return func(a_actor);
    }

    static bool CanFastTravel(RE::Actor* a_actor, bool a_arg2)
    {
        using func_t = decltype(&Utility::CanFastTravel);
        static REL::Relocation<func_t> func{ REL::ID(40444) };
        return func(a_actor, a_arg2);
    }

    static bool IsFastTravelEnabled()
    {
        using func_t = decltype(&Utility::IsFastTravelEnabled);
        REL::Relocation<func_t> func{ REL::ID(55481) };
        return func();
    }

    static void EnableFastTravel(void* a1, void* a2, void* a3, bool a_enable)
    {
        using func_t = decltype(&Utility::EnableFastTravel);
        REL::Relocation<func_t> func{ RELOCATION_ID(54946, 55563) };
        return func(a1, a2, a3, a_enable);
    }
};
