/*
 * =====================================================================================
 *
 *       Filename:  IURLs.hpp
 *
 *    Description:  An interface where you can register your interest in handling certain urls
 *
 *        Version:  1.0
 *        Created:  07/11/11 22:33:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#pragma once

#include "base/URLSignal.hpp"

namespace wittyPlus {

class IURLs {
public:
    virtual base::URLSignal& urlSignal(const string& url) = 0;

    static IURLs* instance();
};

} // namespace wittyPlus
