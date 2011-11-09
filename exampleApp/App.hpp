/*
 * =====================================================================================
 *
 *       Filename:  App.hpp
 *
 *    Description:  Loads the wittyPlus App and our wtExtensions
 *
 *        Version:  1.0
 *        Created:  09/11/11 11:07:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <wittyPlus/App.hpp>
#include <wittyPlus/IURLs.hpp>
#include <wittyPlus/extensions/page/Extension.hpp>

namespace exampleApp {

class App : public wittyPlus::App {
public:
    typedef wittyPlus::page::Extension PageExtension;
private:
    PageExtension* pageExtension;
public:
    App(const WEnvironment& environment) : wittyPlus::App(environment) {
        // Set up the extensions
        pageExtension = new PageExtension(this);
        // Make sure '/' shows the 'index.html' page
        IURLs::instance()->urlSignal("/", true).connect(pageExtension, &PageExtension::show_a_page);
        // Fire an internal path changed event off as user may have navigated straight here
        internalPathChanged().emit(internalPath());
    }
};

} // namespace exampleApp {
