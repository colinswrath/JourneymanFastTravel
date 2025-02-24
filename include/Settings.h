#pragma once

class Settings
{
public:
    static void LoadSettings() noexcept;
    static void UpdateFeatureLocked();

    inline static bool debug_logging{};
    inline static RE::BGSListForm*  RequiredItems{};
    inline static RE::TESGlobal*   Survival_ModeEnabledShared{};
    inline static RE::TESGlobal*    MAG_IsFeatureLocked{};

    inline static bool  needToShowRemoveMessage{};
    inline static bool         menuFastTravel{};
    inline static std::string  RequiredItemNotFoundMessage{};
    inline static std::string  TravelPackRemoveMessage{};
    inline static bool         EnableOnlyOnSM{};
};
