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

		std::string ft(ini.GetValue("","sNoTravelPackMessage","FILL TRAVEL FAILED IN INI"));
		std::string tpr(ini.GetValue("","sTravelPackRemoveMessage","FILL TRAVEL PACK MESSAGE IN INI"));

		RequiredItemNotFoundMessage = ft;
		TravelPackRemoveMessage = tpr;
		logger::info("Message loaded");

		if (settings->RequiredItemNotFoundMessage == "") {
			logger::info("MESSAGE NOT FOUND");
		}

		RequiredItems = RE::TESDataHandler::GetSingleton()->LookupForm(RE::FormID(0x800), "Journeyman.esp")->As<RE::BGSListForm>();
		logger::info("Settings loaded");

	}

	RE::BGSListForm* RequiredItems;
	bool needToShowRemoveMessage = false;
	bool menuFastTravel = false;
	std::string RequiredItemNotFoundMessage = "";
	std::string TravelPackRemoveMessage = "";
};