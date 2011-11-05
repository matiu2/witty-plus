#ifndef WITTYPLUS_EXTENSIONMANAGER_HPP
#define WITTYPLUS_EXTENSIONMANAGER_HPP

#include <Wt/WObject>

namespace wittyPlus {

class App;

/** This class registers extensions
  **/
class ExtensionManager : public Wt::WObject {
    friend class App;
private:
    ExtensionManager(Wt::WObject* parent=0);
public:
    /// The app object associated with this extension manager
    App* app();
    /// Returns the extension manager associated with the WApplication of the current thread
    static ExtensionManager* instance();
};

} // namespace wittyPlus

#endif // WITTYPLUS_EXTENSIONMANAGER_HPP
