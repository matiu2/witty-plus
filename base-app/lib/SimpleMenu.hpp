/** Provides a menu, but all it has is 'internal links' doesn't associate a widget to show with each item.
  * Uses 'ul' for styling and a 'menu' class
  */
#ifndef SIMPLEMENU_HPP
#define SIMPLEMENU_HPP

#include <Wt/WCompositeWidget>
#include <Wt/WContainerWidget>
#include <Wt/WString>
#include <string>
#include <vector>
#include "InternalLink.hpp"

using std::vector;
using Wt::WString;
using Wt::WCompositeWidget;
using Wt::WContainerWidget;
using std::string;

namespace wittyPlus {

class SimpleMenu : public WCompositeWidget {
private:
    WContainerWidget* _impl;
public:
    SimpleMenu(WContainerWidget* parent=0) : WCompositeWidget(parent) {
        setImplementation(_impl = new WContainerWidget());
        _impl->setList(true);
        _impl->setStyleClass("menu");
    }
    void addLink(const WString &text, const string &url) {
        _impl->addWidget(new InternalLink(url, text));
    }
};

} // namespace wittyPlus

#endif // SIMPLEMENU_HPP
