/*
 * =====================================================================================
 *
 *       Filename:  URLs.hpp
 *
 *    Description:  A map between a url and a signal to run when it's navigated to
 *
 *        Version:  1.0
 *        Created:  10/08/11 22:10:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <Wt/WObject>
#include <Wt/WSignal>
#include <Wt/WApplication>
#include "URLSignal.hpp"

using Wt::WObject;
using Wt::Signal;

namespace wittyPlus {
namespace base {

/** 
  * A base class with a map of urls to signals. When a certain url is hit .. the signal is called.
  * Witty already has a signal that is fired on practically every url change. This class tries to use 
  * the power of map to make things a bit more effecient and hold a giant runtime repository.
 **/
class URLs : public WObject {
public:
    typedef void (*Handler)();
    typedef std::map<std::string, base::URLSignal*> URLMap;
    typedef std::pair<std::string, base::URLSignal*> URLPair;
    typedef std::pair<const std::string&, base::URLSignal*> URLConstPair;
private:
    URLMap urlMap;
    /// Used to find the url by the start bit .. WARNING: it assumes 'a' is always equal to app->internalPath() (which seems to be the case on my desktop)
    static bool compareFunc(const URLConstPair& a, const URLConstPair& b) {
        // true if a starts with b
        return a.first.compare(0, b.first.length(), b.first) == 0;
    }
public:
    URLs(Wt::WObject* parent=0) : WObject(parent) {}
    /** Returns an existing signal handler, or create's a new one on the fly and returns it,
      * with 'override' it'll replace an old one instead of returning it
      * @param url the user navigates to to fire the signal
      * @param override if true, deletes any old signal handlers we find
     **/
    URLSignal& urlSignal(const string& url, bool override=false) {
        URLSignal*& result = urlMap[url]; // Needs to be a reference to a pointer because we set it below
        if (override && (result != 0)) {
            delete result;
            result = 0;
        }
        if (result == 0) {
            result = new URLSignal(this);
        }
        return *result;
    }
    void run(const string& url) {
        // Find the longest registered url that matches the start of the passed in url
        // For example: url="/page/4" and we have: "/" and "/pa" and "/page" .. "/page"'s signal would be fired
        string searchingFor = url.length() == 0 ? "/" : url;
        while (searchingFor.length() > 0) {
            URLMap::iterator i = urlMap.find(searchingFor);
            if (i != urlMap.end()) {
                i->second->emit();
                break;
            } else {
                size_t lastSlash = searchingFor.rfind('/');
                if (lastSlash != searchingFor.npos)
                    searchingFor.erase(lastSlash);
            }
        }
    }
};

} // namespace base
} // namespace wittyPlus