# C++ implementation of Message Digest 5 (MD5)
Simple C++ MD5 implementation based on [RFC-1321](https://tools.ietf.org/html/rfc1321) document

# Example

1. With i/o streams

    ```c++
        HasherMD5 h;
        std::cin >> h;
        std::cout << h;
    ```

2. Pass string in constructor

    ```c++
        std::string testString = "abcde";
        HasherMD5 h(testString);
        std::cout << h << std::endl;
    ```
3. Pass string to 'hashString' method
   ```c++
        std::string testString = "abcde";
        HasherMD5 h;
        h.hashString(testString);
        std::cout << h.getHashedString() << std::endl;
   ```
4. Multiple rounds of hashing
   ```c++
       std::string testString = "abcde";
       HasherMD5 h(testString);
   
       for(int i = 0; i < 5; i++) {
           h.hashString(h.getHashedString());
           std::cout << h << std::endl;
       }
   
   ```
5. File hashing
    ```c++
       HasherMD5 h;
       h.hashString(utils::readFileIntoString("test.txt"));
       std::cout << h << std::endl;
    ```
   or (if you do not want to use function from utils)
    ```c++
       HasherMD5 h;
       std::ifstream file(filepath, std::ios::binary);
   
       std::string fileContent((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
   
       h.hashString(fileContent);
       std::cout << h << std::endl;
    ```
   
---
# Warning

You should not use MD5 unless you have to!

This algorithm is not secure anymore