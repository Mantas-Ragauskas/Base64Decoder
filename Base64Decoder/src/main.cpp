

#include <iostream>
#include "../headers/Base64Decoder.h"


int main()
{
    string endcodedString  = "SGVsbG8gV29ybGQh";
   /* 
   std::cout << "Enter encoded string: " << "\r\n";
    std::cin >> endcodedString;
    */
    string decodedString = Base64Decoder::Decode(endcodedString);
    std::cout << "Decoded string:  -" << decodedString << "-\r\n";
    int i;
    std::cin >> i;
    return 0;
}

