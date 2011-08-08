/*
 * =====================================================================================
 *
 *       Filename:  UserManager.cpp
 *
 *    Description:  Manages user logins using mong DB for storage
 *
 *        Version:  1.0
 *        Created:  06/01/2011 10:57:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "UserManager.hpp"
#include <openssl/sha.h>

/**
* @brief c++ version of SHA1. Pass input string, get a hash.
*
* @param input the string to have sha run on
* @param value auto pointer to the SHAValue
*/
void sha1(const std::string input, SHAValue& value) {
    SHA1(reinterpret_cast<const unsigned char*>(&input[0]), input.length(), &(value[0])); // Make a hash of the password supplied
}
