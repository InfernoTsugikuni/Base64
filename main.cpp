#include <iostream>
#include "base64.h"

int main() {
    std::string data = "Something";

    // Encode data
    std::string encodedData = Base64::Encode(data);
    std::cout << "Encoded: " << encodedData << std::endl;

    // Decode data
    std::string decodedData = Base64::Decode(encodedData);
    std::cout << "Decoded: " << decodedData << std::endl;

    return 0;
}
