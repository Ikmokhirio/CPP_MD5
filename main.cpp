#include "HasherMD5.h"

int main() {

    HasherMD5 h;
    h.hashString(utils::readFileIntoString("test.txt")); // Getting hash from file example
    std::cout << h.getHashedString() << std::endl;

    h.hashString("abcde"); // Getting hash from string
    std::cout << h << std::endl;

    h.hashString(h.getHashedString()); // Getting hash from previous hash
    std::cout << h << std::endl;

}