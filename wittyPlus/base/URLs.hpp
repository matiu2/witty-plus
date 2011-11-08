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
private:
    URLMap urlMap;
public:
    URLs(WObject* parent=0) : WObject(parent) {}
    URLSignal& operator[](const string& url) { 
        URLSignal*& result = urlMap[url];
        if (result == 0) {
            result = new URLSignal(this);
        }
        return *result;
    }
    void run(const string& url) {
        URLMap::iterator found = urlMap.find(url);
        if (found != urlMap.end())
            found->second->emit();
    }
};

} // namespace base
} // namespace wittyPlus
