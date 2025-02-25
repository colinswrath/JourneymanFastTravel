#include "Settings.h"

void Settings::LoadSettings() noexcept
{
    logger::info("Loading settings");

    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\Journeyman.ini)");
    const auto dataHandler = RE::TESDataHandler::GetSingleton();

    std::string ft(ini.GetValue("", "sNoTravelPackMessage", ""));
    std::string tpr(ini.GetValue("", "sTravelPackRemoveMessage", "FILL TRAVEL PACK MESSAGE IN INI"));

    EnableOnlyOnSM = ini.GetBoolValue("", "bEnableOnlyOnSurvivalEnabled");

    RequiredItemNotFoundMessage = ft;
    TravelPackRemoveMessage     = tpr;
    logger::info("Message loaded");

    if (RequiredItemNotFoundMessage == "") {
        logger::info("MESSAGE NOT FOUND");
    }

    RequiredItems       = RE::TESDataHandler::GetSingleton()->LookupForm(RE::FormID(0x800), "Journeyman.esp")->As<RE::BGSListForm>();
    MAG_IsFeatureLocked = RE::TESDataHandler::GetSingleton()->LookupForm(RE::FormID(0x80A), "Journeyman.esp")->As<RE::TESGlobal>();
    UpdateFeatureLocked();
    Survival_ModeEnabledShared = dataHandler->LookupForm(RE::FormID(0x314A), "Update.esm")->As<RE::TESGlobal>();
    logger::info("Settings loaded");
}

void Settings::UpdateFeatureLocked() { MAG_IsFeatureLocked->value = EnableOnlyOnSM; }
