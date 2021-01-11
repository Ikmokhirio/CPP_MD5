//
// Created by Ikmokhirio on 04.01.2021.
//

#include "utils.h"

uint32_t utils::shiftLeft(uint32_t val, uint32_t pos) {
    uint32_t res = val;
    return ((res << pos) | (res >> (sizeof(uint32_t) * CHAR_BIT - pos)));
}

std::string utils::readFileIntoString(const std::string &filepath) {
    std::ifstream file(filepath, std::ios::binary);

    std::string fileContent((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());

    return fileContent;
}
