/*
 * =====================================================================================
 *
 *       Filename:  URLSignal.hpp
 *
 *    Description:  Just used so we can define URLSignal in one place without creating a lot of import dependencies everywhere
 *
 *        Version:  1.0
 *        Created:  07/11/11 22:40:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#pragma once

#include <Wt/WSignal>

namespace wittyPlus {
namespace base {
    typedef Wt::Signal<> URLSignal;
} // namespace base
} // namespace wittyPlus
