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
    /** Returns an existing signal handler .. or create's a new one on the fly and returns it
      * @param url the user navigates to to fire the signal
      * @param override if true, deletes any old signal handlers we find
     **/
    virtual base::URLSignal& urlSignal(const std::string& url, bool override=false) = 0;

    static IURLs* instance();
};

} // namespace wittyPlus
