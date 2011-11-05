#ifndef WITTYPLUS_EXTENSIONMANAGER_HPP
#define WITTYPLUS_EXTENSIONMANAGER_HPP

#include <Wt/WObject>

namespace wittyPlus {

class App;

/** This class registers extensions
  **/
class ExtensionManager : public Wt::WObject {
private:
    ExtensionManager(WObject* parent);
public:
    /// Returns the extension manager associated with the WApplication of the current thread
    static ExtensionManager* instance();
};

} // namespace wittyPlus

#endif // WITTYPLUS_EXTENSIONMANAGER_HPP
