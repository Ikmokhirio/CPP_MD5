//
// Created by Ikmokhirio on 04.01.2021.
//

#include "HasherMD5.h"

void HasherMD5::hashString(const std::string &stringToHash) {
    if (!stringToHash.empty()) {
        this->stringToHash = stringToHash;
    }

    splitStringToBlocks();
    hashedString = generateHash();
}

void HasherMD5::splitStringToBlocks() {

    clearPreviousBlocks();

    unsigned amountOfIntsInBlock = DEFAULT_BLOCK_SIZE / (CHAR_BIT * sizeof(uint32_t));

    std::string input = adjustMessagePadding();

    unsigned amountOfBlocks = input.size() * sizeof(char) * CHAR_BIT / 512;

    int counter = 0;
    for (int i = 0; i < amountOfBlocks; i++) {
        std::vector<uint32_t> tmpVec;

        for (int j = 0; j < amountOfIntsInBlock; j++) {

            uint32_t value = 0;
            memcpy(&value, input.c_str() + (sizeof(uint32_t) * counter), sizeof(uint32_t));
            tmpVec.push_back(value); // Add value in little endian

            counter++;
        }

        blocks.push_back(tmpVec);
    }

}

std::string HasherMD5::adjustMessagePadding() {
    std::string message = stringToHash;

    uint64_t len = message.size() * sizeof(char) * CHAR_BIT; // Length of message in bits

    message += static_cast<char>(1 << (CHAR_BIT - 1)); // Add 10000000 to the end of message

    while (message.size() * sizeof(char) * CHAR_BIT % DEFAULT_BLOCK_SIZE != 448) {
        message += FILLER;
    }

    for (int i = 0; i < sizeof(uint64_t); i++) {
        message += static_cast<char>(len >> (CHAR_BIT * i)); // Add message length as little endian by byte
    }


    while (message.size() * sizeof(char) * CHAR_BIT % DEFAULT_BLOCK_SIZE != 0) {
        message += FILLER;
    }

    return message;
}

std::string HasherMD5::generateHash() {
    std::vector<uint32_t> intermediateHashes;
    intermediateHashes.push_back(0x67452301);
    intermediateHashes.push_back(0xEFCDAB89);
    intermediateHashes.push_back(0x98BADCFE);
    intermediateHashes.push_back(0x10325476);

    int counter = 0;
    for (auto &block : blocks) {

        std::vector<uint32_t> wordBuffer = intermediateHashes;

        //Process one block
        wordBuffer = processNextBlock(block, wordBuffer);


        for (int i = 0; i < intermediateHashes.size(); i++) {
            intermediateHashes[i] += wordBuffer[i];
        }

        counter++;
    }

    std::stringstream ss;
    for (unsigned int intermediateHash : intermediateHashes) {
        ss << std::setfill('0') << std::setw(8) << std::hex << BYTE_SWAP(intermediateHash); // Output in little endian
    }

    return ss.str();
}

std::vector<uint32_t> HasherMD5::processNextBlock(std::vector<uint32_t> block, std::vector<uint32_t> wordBuffer) {

    auto t = [](uint32_t n) { // Correct
        return ((uint32_t) (pow(2, 32) * abs(sin(n))));
    };

    auto f = [](uint32_t x, uint32_t y, uint32_t z) {
        return ((x & y) | (~x & z));
    };

    auto g = [](uint32_t x, uint32_t y, uint32_t z) {
        return ((x & z) | (~z & y));
    };

    auto h = [](uint32_t x, uint32_t y, uint32_t z) {
        return (x ^ y ^ z);
    };

    auto i = [](uint32_t x, uint32_t y, uint32_t z) {
        return (y ^ (~z | x));
    };


    for (int k = 0; k < 64; k++) {


        uint32_t result = 0;
        int j;

        std::vector<uint32_t> s;

        if (k < 16) {

            s.push_back(7);
            s.push_back(12);
            s.push_back(17);
            s.push_back(22);

            j = k;
            result = f(wordBuffer[1], wordBuffer[2], wordBuffer[3]) + wordBuffer[0] + block[j] + t(k + 1);

        } else if (k < 32) {

            s.push_back(5);
            s.push_back(9);
            s.push_back(14);
            s.push_back(20);

            j = (5 * k + 1) % 16;
            result = g(wordBuffer[1], wordBuffer[2], wordBuffer[3]) + wordBuffer[0] + block[j] + t(k + 1);
        } else if (k < 48) {

            s.push_back(4);
            s.push_back(11);
            s.push_back(16);
            s.push_back(23);

            j = (3 * k + 5) % 16;
            result = h(wordBuffer[1], wordBuffer[2], wordBuffer[3]) + wordBuffer[0] + block[j] + t(k + 1);
        } else if (k < 64) {

            s.push_back(6);
            s.push_back(10);
            s.push_back(15);
            s.push_back(21);

            j = (7 * k) % 16;
            result = i(wordBuffer[1], wordBuffer[2], wordBuffer[3]) + wordBuffer[0] + block[j] + t(k + 1);
        }

        wordBuffer[0] = wordBuffer[3];
        wordBuffer[3] = wordBuffer[2];
        wordBuffer[2] = wordBuffer[1];
        wordBuffer[1] = wordBuffer[1] + utils::shiftLeft(result, s[k % 4]);

    }

    return wordBuffer;
}

std::ostream &operator<<(std::ostream &os, HasherMD5 &hasher) {
    os << hasher.getHashedString();
    return os;
}

std::istream &operator>>(std::istream &is, HasherMD5 &hasher) {
    std::string inputString;
    is >> inputString;
    hasher.hashString(inputString);
    return is;
}

std::string HasherMD5::getHashedString() {
    return hashedString;
}

void HasherMD5::clearPreviousBlocks() {
    std::vector<std::vector<uint32_t>> tmpBlocks;
    blocks.swap(tmpBlocks);
}

HasherMD5::HasherMD5(const std::string &inputString) {
    if (!inputString.empty()) {
        hashString(inputString);
    }
}
