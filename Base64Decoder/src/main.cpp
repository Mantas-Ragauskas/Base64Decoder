#include <iostream>
#include "../headers/Base64Decoder.h"

using std::string; 

int main()
{
    /* Sample string: "Hello, World!"                */
    /* Encoded:       "SGVsbG8sIFdvcmxkIQ=="         */
    /* Encoded using https://www.base64encode.org/   */       
    /*
    string endcodedString  = "SGVsbG8sIFdvcmxkIQ==";
    */

    string endcodedString = "";
    std::cout << "Enter encoded string: " << "\r\n";
    std::cin >> endcodedString;

    string decodedString = Base64Decoder::Decode(endcodedString);
    std::cout << "Decoded string: " << decodedString << "\r\n";
    int i;
    std::cin >> i;
    return 0;
}

