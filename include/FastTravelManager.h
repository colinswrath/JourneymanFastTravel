#pragma once

class FastTravelManager
{
public:
    static bool InstallCanFastTravelCheck();
    static bool InstallPapyrusFastTravelCheck();

    inline static RE::TESWorldSpace*                           GetWorldSpaceHook(RE::TESObjectREFR* a1);
    inline static REL::Relocation<decltype(GetWorldSpaceHook)> _GetWorldSpaceHook;
    inline static bool                                         CanFastTravelMap(RE::Actor* actor, bool a_bool);
    inline static REL::Relocation<decltype(CanFastTravelMap)>  _CanFastTravelMap;
};
