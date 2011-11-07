#ifndef WITTYPLUS_EXTENSIONMANAGER_HPP
#define WITTYPLUS_EXTENSIONMANAGER_HPP

#include <Wt/WObject>

namespace wittyPlus {

class App;

/** This class registers extensions
  **/
class ExtensionManager : public Wt::WObject {
    friend class App; // Only App can create us
private:
    ExtensionManager(Wt::WObject* parent=0);
public:
    /// Returns the extension manager associated with the WApplication of the current thread
    static ExtensionManager* instance(); // Only one instance per App/thread
};

} // namespace wittyPlus

#endif // WITTYPLUS_EXTENSIONMANAGER_HPP
