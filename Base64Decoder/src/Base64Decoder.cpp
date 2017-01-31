#include "../headers/Base64Decoder.h"
#include <String>

using std::string;

const string Base64Decoder::base64_chars = 
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/********************************************************************************/
uint8_t Base64Decoder::DecodeBase64Character(char encodedCharacter)
    {
    int8_t index = base64_chars.find(encodedCharacter);
    return (index != -1) ? index : 0;
    }

/********************************************************************************/
bool Base64Decoder::ValidateSring(const string& encodedString)
    {
    uint32_t length = encodedString.length();
    int32_t  paddingPos;
    
    if ((length < 4) || (0 != length % 4))
        return false;

    paddingPos = encodedString.find("=", length - 4);
    length = (-1 == paddingPos) ? length : paddingPos-1;

    for (int i = 1; i < length; i++)
        {
        if (-1 == base64_chars.find(encodedString[i]))
            return false;
        }
    return true;
    }

/********************************************************************************/
uint32_t Base64Decoder::FillBuffer(const string &encodedBlock)
    {
    uint32_t buffer = 0;
    buffer += DecodeBase64Character(encodedBlock[0]) << 18;
    buffer += DecodeBase64Character(encodedBlock[1]) << 12;
    buffer += DecodeBase64Character(encodedBlock[2]) << 6;
    buffer += DecodeBase64Character(encodedBlock[3]) << 0;
    return buffer;
    }


/********************************************************************************/
/* Note:                                                                        */
/* When filling the buffer, padding symbol "=" is added as a 0 value,           */
/* which coresponds to null string.                                             */
/* Appending null string does not change the string.                            */
/* While appending null up to 3 times is not very elegant, it does reduce       */
/* complexity of verification logic considerably.                               */
/* Must be aware of this in case there are changes to std:string:append()       */
/********************************************************************************/
string Base64Decoder::DecodeBuffer(uint32_t buffer)
    {    
    string decodedBUffer = "";
    decodedBUffer.append(1, (buffer & 0x00FF0000) >> 16);
    decodedBUffer.append(1, (buffer & 0x0000FF00) >> 8);
    decodedBUffer.append(1, (buffer & 0x000000FF) >> 0);
    return decodedBUffer;
    }

/********************************************************************************/
string Base64Decoder::Decode(string encodedString)
    {
    string   decodedString = "";
    if (!ValidateSring(encodedString))
        return decodedString;

    for (int i = 0; i <= encodedString.length()-4; i+=4)
        { 
        uint32_t buffer = FillBuffer(encodedString.substr(i, 4));
        decodedString.append(DecodeBuffer(buffer));
        }

    return decodedString;
    }
/********************************************************************************/
