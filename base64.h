#ifndef BASE64_H
#define BASE64_H

#include <string>
#include <stdexcept>

class Base64 {
public:
    static std::string Encode(const std::string& data) {
        static const char base64Chars[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

        std::string encoded;
        int val = 0;
        int valb = -6;

        for (unsigned char c : data) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                encoded.push_back(base64Chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }

        if (valb > -6) {
            encoded.push_back(base64Chars[((val << 8) >> (valb + 8)) & 0x3F]);
        }

        while (encoded.size() % 4) {
            encoded.push_back('=');
        }

        return encoded;
    }

    static std::string Decode(const std::string& base64Data) {
        static const int decodingTable[256] = {
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 62,-1,-1,-1, 63,
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61,-1,-1,-1,  0,-1,-1,
            -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
            15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
            -1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
            41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
        };

        std::string decoded;
        int val = 0;
        int valb = -8;

        for (unsigned char c : base64Data) {
            if (decodingTable[c] == -1) break;
            val = (val << 6) + decodingTable[c];
            valb += 6;
            if (valb >= 0) {
                decoded.push_back(char((val >> valb) & 0xFF));
                valb -= 8;
            }
        }

        return decoded;
    }
};

#endif // BASE64_H
