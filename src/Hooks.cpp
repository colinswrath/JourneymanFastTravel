#include "Hooks.h"
#include "FastTravelManager.h"

namespace Hooks
{
    void Install() noexcept
    {
        FastTravelManager::InstallCanFastTravelCheck();
        FastTravelManager::InstallPapyrusFastTravelCheck();
    }
} // namespace Hooks
