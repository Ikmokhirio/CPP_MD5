//
// Created by Ikmokhirio on 04.01.2021.
//

#ifndef SHA_1_UTILS_H
#define SHA_1_UTILS_H

#include <climits>
#include <cstdint>
#include <string>
#include <fstream>
#include <streambuf>

#ifdef _MSC_VER
#define BYTE_SWAP(value) _byteswap_ulong(value)
#elif defined(__GNUC__)
#define BYTE_SWAP(value) __builtin_bswap32(value)
#elif defined(__MINGW32__)
#define BYTE_SWAP(value) __builtin_bswap32(value)
#elif defined(__MINGW64__)
#define BYTE_SWAP(value) __builtin_bswap32(value)
#endif


class utils {
public:
    static uint32_t shiftLeft(uint32_t val, uint32_t pos); // Left Circular Shift

    static std::string readFileIntoString(const std::string &filepath);
};


#endif //SHA_1_UTILS_H
