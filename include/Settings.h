#pragma once

#include <SimpleIni.h>

class Settings
{
public:
	static Settings* GetSingleton()
	{
		static Settings playerStatus;
		return &playerStatus;
	}

	void LoadSettings() 
	{
		logger::info("Loading settings");
		auto settings = Settings::GetSingleton();

		CSimpleIniA ini;
		ini.SetUnicode();
		ini.LoadFile(R"(.\Data\SKSE\Plugins\Journeyman.ini)");
		const auto dataHandler = RE::TESDataHandler::GetSingleton();

		std::string ft(ini.GetValue("","sNoTravelPackMessage",""));
		std::string tpr(ini.GetValue("","sTravelPackRemoveMessage","FILL TRAVEL PACK MESSAGE IN INI"));

		EnableOnlyOnSM = ini.GetBoolValue("", "bEnableOnlyOnSurvivalEnabled");

		RequiredItemNotFoundMessage = ft;
		TravelPackRemoveMessage = tpr;
		logger::info("Message loaded");

		if (settings->RequiredItemNotFoundMessage == "") {
			logger::info("MESSAGE NOT FOUND");
		}

		RequiredItems = RE::TESDataHandler::GetSingleton()->LookupForm(RE::FormID(0x800), "Journeyman.esp")->As<RE::BGSListForm>();
		MAG_IsFeatureLocked = RE::TESDataHandler::GetSingleton()->LookupForm(RE::FormID(0x854), "Journeyman.esp")->As<RE::TESGlobal>();

		MAG_IsFeatureLocked->value = EnableOnlyOnSM;

		Survival_ModeEnabledShared = dataHandler->LookupForm(RE::FormID(0x314A), "Update.esm")->As<RE::TESGlobal>();
		logger::info("Settings loaded");

	}

	RE::BGSListForm* RequiredItems;
	RE::TESGlobal* Survival_ModeEnabledShared;
	RE::TESGlobal* MAG_IsFeatureLocked;

	bool needToShowRemoveMessage = false;
	bool menuFastTravel = false;
	std::string RequiredItemNotFoundMessage = "";
	std::string TravelPackRemoveMessage = "";
	bool EnableOnlyOnSM = false;
};