/*
 * =====================================================================================
 *
 *       Filename:  page.cpp
 *
 *    Description:  A plugin that provides a single page
 *
 *        Version:  1.0
 *        Created:  13/10/11 02:29:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#pragma once
#include <Wt/WObject>

namespace wittyPlus {
namespace page {

/// A singleton that will be created when the plugin is loaded by the main app. Not thread safe.
class Extension: public WObject {
public:
    const string& name() { return "Page"; }
};

} // namespace page
} // namespace wittyPlus
