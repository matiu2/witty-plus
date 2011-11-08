#include "ExtensionManager.hpp"

#include <Wt/WObject>
#include <wittyPlus/App.hpp>
#include <memory>

// Pull in all the dependent libs
#ifdef EXT_PAGE
#include "page/Extension.hpp"
#endif //  EXT_PAGE

namespace wittyPlus {

namespace {
    std::unique_ptr<ExtensionManager> globalInstance;
}

// Public Methods
ExtensionManager::ExtensionManager() {
    // Load all the extensions
    #ifdef EXT_PAGE
    registerExtension(std::unique_ptr<wittyPlus::Extension>(new page::Extension()));
    #endif
}

// Static funcs
ExtensionManager& ExtensionManager::instance() {
    if (!globalInstance)
        globalInstance.reset(new ExtensionManager());
    return *globalInstance;
}

} // namespace wittyPlus
