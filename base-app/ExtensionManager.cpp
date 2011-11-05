#include "ExtensionManager.hpp"

#include <Wt/WApplication>
#include "App.hpp"

namespace wittyPlus {

ExtensionManager::ExtensionManager(WObject* parent) : WObject(parent) {

}

// Static funcs

ExtensionManager* ExtensionManager::instance() {
    Wt::WApplication* app = Wt::WApplication::instance();
    return app->extensionManager();
}

} // namespace wittyPlus
