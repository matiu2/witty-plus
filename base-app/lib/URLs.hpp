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

using Wt::WObject;
using Wt::Signal;

namespace wittyPlus {
namespace base {

class URLs : public WObject {
public:
    typedef Signal<> URLSignal;
    typedef void (*Handler)();
    typedef map<string, URLSignal*> URLMap;
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
