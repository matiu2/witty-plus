#pragma once

#include <string>
#include <map> 
#include <assert.h>
#include <memory>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
#include "extensions/Extension.hpp"

namespace Wt {
    class WObject;
}


namespace wittyPlus {

class App;

// TODO: Make this map to a threadsafe store .. it's read a lot write a little .. so perhaps a map to factories shared
// between threads

/** This class registers extensions .. it is a thread safe Singleton
  **/
class ExtensionManager {
public:
    typedef std::map<std::string, std::unique_ptr<Extension> > ExtensionMap;
    typedef std::pair<std::string, std::unique_ptr<Extension> > ExtensionPair;
private:
    ExtensionMap _extensions;
    mutable boost::shared_mutex _lock; // Many can read _extensions (all the Apps) .. but everyone has to wait for a writer
    ExtensionManager() {} // Only App can create instances of this class
public:
    /// Returns the extension manager associated with the WApplication of the current thread
    static ExtensionManager& instance(); // Only one global instance for all apps and all threads
    /// Call to register a new extension
    void registerExtension(std::unique_ptr<Extension> extension) { 
        boost::lock_guard<boost::shared_mutex> lock(_lock);
        const std::string& name = extension->name();
        ExtensionMap::iterator i = _extensions.find(name);
        assert( i != _extensions.end() ); // We shouldn't have one already here .. registering twice is not allowed
        _extensions.insert(ExtensionPair(name, std::move(extension)));
    }
    /** Find an extension by name.
        @return 0 if extension not registered
     **/
    Extension* findExtension(const std::string& name) {
        boost::shared_lock<boost::shared_mutex> readLock(_lock);
        ExtensionMap::iterator i = _extensions.find(name);
        return i == _extensions.end() ? 0 : i->second.get();
    }
    /** Launches all the extensions for the current app/thread
      **/
    void launchExtensions(Wt::WObject* parent) const {
        boost::shared_lock<boost::shared_mutex> readLock(_lock);
        for (ExtensionMap::const_iterator i=_extensions.begin(); i!=_extensions.end(); ++i) {
            i->second->launch(parent);
        }
    }
};

} // namespace wittyPlus
