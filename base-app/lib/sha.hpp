/*
 * =====================================================================================
 *
 *       Filename:  sha.hpp
 *
 *    Description:  SHA hasing algorithm bits and pieces
 *
 *        Version:  1.0
 *        Created:  08/15/11 23:14:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SHA_HPP
#define SHA_HPP

#include <openssl/sha.h>
#include <vector>
#include <string>

namespace wittyPlus {
namespace base {

const unsigned int SHALength = 20;
typedef unsigned char SHAValue[SHALength];
typedef std::vector<unsigned char> StdSHAValue;
using std::string;

/**
* @brief c++ version of SHA1. Pass input string, get a hash.
*
* @param input the string to have sha run on
* @param value auto pointer to the SHAValue
*/
inline void sha1(const std::string& input, SHAValue& value) {
    SHA1(reinterpret_cast<const unsigned char*>(&input[0]), input.length(), &(value[0])); // Make a hash of the password supplied
}

/**
* @brief c++ version of SHA1. Pass input string, get a hash.
*
* @param input the string to have sha run on
*
* @return The hash of the string
*/
inline StdSHAValue sha1(const std::string& input) {
    StdSHAValue result(SHALength, 0);
    SHA1(reinterpret_cast<const unsigned char*>(&input[0]), input.length(), &(result[0])); // Make a hash of the password supplied
    return result;
}

} // namespace base
} // namespace wittyPlus

#endif //  SHA_HPP
