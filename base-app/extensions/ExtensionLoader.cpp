#include "ExtensionLoader.hpp"
#include "ExtensionManager.hpp"

// Specify includes for each extension
#ifdef EXT_PAGE
#include "page/Extension.hpp"
#endif

namespace wittyPlus {

void ExtensionLoader::loadExtensions() {
    ExtensionManager& manager = ExtensionManager::instance();
    #ifdef EXT_PAGE
    manager.registerExtension(std::unique_ptr<wittyPlus::Extension>(new page::Extension()));
    #endif
}

} // namespace wittyPlus
