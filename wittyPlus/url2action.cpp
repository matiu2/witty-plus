/*
 * =====================================================================================
 *
 *       Filename:  url2action.cpp
 *
 *    Description:  Handles base app mapping of urls to actions, plus registering interest of extensions.
 *
 *        Version:  1.0
 *        Created:  07/11/11 22:43:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "url2action.hpp"

namespace wittyPlus {

base::URLSignal& URL2Action::urlSignal(const string& url) {
    return _urls[url];
}

} // namespace wittyPlus
