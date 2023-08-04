#include "Hooks.h"
#include "Settings.h"
#include "Events.h"
#include <stddef.h>

namespace {
    
    void InitializeLogging() {
        auto path = SKSE::log::log_directory();
        if (!path) {
            SKSE::stl::report_and_fail("Unable to lookup SKSE logs directory.");
        }
        *path /= SKSE::PluginDeclaration::GetSingleton()->GetName();
        *path += L".log";

        std::shared_ptr<spdlog::logger> log;
        if (IsDebuggerPresent()) {
            log = std::make_shared<spdlog::logger>(
                "Global", std::make_shared<spdlog::sinks::msvc_sink_mt>());
        } else {
            log = std::make_shared<spdlog::logger>(
                "Global", std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));
        }
        log->set_level(spdlog::level::info);
        log->flush_on(spdlog::level::info);

        spdlog::set_default_logger(std::move(log));
        spdlog::set_pattern("[%H:%M:%S.%e]: %v");
    }
}

void InitListener(SKSE::MessagingInterface::Message* a_msg)
{
    switch (a_msg->type)
    {
    case SKSE::MessagingInterface::kNewGame:
    case SKSE::MessagingInterface::kDataLoaded:

        Settings::GetSingleton()->LoadSettings();
        break;
    case SKSE::MessagingInterface::kPostLoadGame:
        Settings::GetSingleton()->UpdateFeatureLocked();
    }
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface * a_skse)
{
    InitializeLogging();
    SKSE::Init(a_skse);

    auto pluginDec = SKSE::PluginDeclaration::GetSingleton();

    logger::info(FMT_STRING("Loading Fast Travel{}"), pluginDec->GetVersion());

    SKSE::AllocTrampoline(48);

    if (!Hooks::Install())
    {
        logger::error("Install fast travel hooks failed");
        return false;
    }

    auto messaging = SKSE::GetMessagingInterface();
    if (!messaging->RegisterListener(InitListener))
    {
        return false;
    }

    Events::OnFastTravelEndEventHandler::Register();
    Events::OnMenuCloseHandler::Register();

    //Settings::LoadJsonFile();
    //Settings::ParsePreLoadSettings();

    logger::info("Fast Travel loaded");

    return true;
}