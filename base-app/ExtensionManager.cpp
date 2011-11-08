#include "ExtensionManager.hpp"

#include <Wt/WObject>
#include "App.hpp"
#include <memory>

namespace wittyPlus {

// Static funcs

std::unique_ptr<ExtensionManager> globalInstance;

ExtensionManager& ExtensionManager::instance() {
    if (!globalInstance)
        globalInstance.reset(new ExtensionManager());
    return *globalInstance;
}

} // namespace wittyPlus
