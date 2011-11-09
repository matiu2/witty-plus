#pragma once

#include <string>
#include <map> 
#include <assert.h>
#include <memory>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
#include "Extension.hpp"

namespace Wt {
    class WObject;
}

namespace wittyPlus {

class App;

// TODO: Make this map to a threadsafe store .. it's read a lot write a little .. so perhaps a map to factories shared
// between threads

/** This class registers extensions .. it is a thread safe Singleton.
  * It was really made so extensions can be modules .. loaded on the fly .. but now we're not going down that path
  * So it was a waste of time .. I'll delete it soon :)
  **/
class ExtensionManager {
public:
    typedef std::map<std::string, std::unique_ptr<Extension> > ExtensionMap;
    typedef std::pair<std::string, std::unique_ptr<Extension> > ExtensionPair;
private:
    ExtensionMap _extensions;
    mutable boost::shared_mutex _lock; // Many can read _extensions (all the Apps) .. but everyone has to wait for a writer
    ExtensionManager(); // Not creatable .. use instance()
public:
    /// Returns the extension manager associated with the WApplication of the current thread
    static ExtensionManager& instance(); // Only one global instance for all apps and all threads
    /// Call to register a new extension
    void registerExtension(std::unique_ptr<Extension> extension) { 
        boost::lock_guard<boost::shared_mutex> lock(_lock);
        const std::string& name = extension->name();
        ExtensionMap::iterator i = _extensions.find(name);
        assert( i == _extensions.end() ); // We shouldn't have one already here .. registering twice is not allowed
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
      * @param the owner object for the extension implementations
      **/
    void launchExtensions(Wt::WObject* parent) const {
        boost::shared_lock<boost::shared_mutex> readLock(_lock);
        for (ExtensionMap::const_iterator i=_extensions.begin(); i!=_extensions.end(); ++i) {
            i->second->launch(parent);
        }
    }
    /** Launches all the extensions for the current app/thread
      * @param the owner object for the extension implementations
      * @param extensions a reference to a dictionary that will be filled with the implementations indexed by name
      **/
    void launchExtensions(Wt::WObject* parent, std::map<std::string, Wt::WObject*>& extensions) const {
        boost::shared_lock<boost::shared_mutex> readLock(_lock);
        for (ExtensionMap::const_iterator i=_extensions.begin(); i!=_extensions.end(); ++i) {
            extensions.insert(make_pair(i->first,  i->second->launch(parent)));
        }
    }
};

} // namespace wittyPlus
