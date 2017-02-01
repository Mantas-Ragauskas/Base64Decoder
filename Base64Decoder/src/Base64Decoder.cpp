#include <String>
#include "../headers/Base64Decoder.h"

using std::string;

/*******************************************************************************/
/* Found this idea of encoded character to integer conversion                  */
/* on http://www.adp-gmbh.ch/cpp/common/base64.html                            */
/*          (original code by René Nyffenegger)                                */
/*******************************************************************************/
const string Base64Decoder::base64_chars = 
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/********************************************************************************/
/*                                                                              */
/********************************************************************************/
bool Base64Decoder::ValidateSring(const string& encodedString)
    {
    uint32_t length     = encodedString.length();
    int32_t  paddingPos = -1;
    
    if ((length < 4) || (0 != length % 4))
        return false;

    paddingPos = encodedString.find("=", length - 3);
    length = (-1 == paddingPos) ? length : paddingPos;

    for (int i = 1; i < length; i++)
        {
        if (-1 == base64_chars.find(encodedString[i]))
            return false;
        }
    return true;
    }

/********************************************************************************/
/*                                                                              */
/********************************************************************************/
uint32_t Base64Decoder::FillBuffer(const string &encodedBlock)
{
    uint32_t buffer = 0;
    buffer += base64_chars.find(encodedBlock[0]) << 18;
    buffer += base64_chars.find(encodedBlock[1]) << 12;
    buffer += base64_chars.find(encodedBlock[2]) << 6;
    buffer += base64_chars.find(encodedBlock[3]) << 0;
    return buffer;
}

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
/*                                                                              */
/* Note: padding value ranges from 1 to 3                                       */
/********************************************************************************/
uint32_t Base64Decoder::FillPaddedBuffer(const string& encodedBlock, uint8_t padding)
    {
    uint32_t buffer = 0;
    buffer += base64_chars.find(encodedBlock[0]) << 18;
    
    if (2 <= padding)
        buffer += base64_chars.find(encodedBlock[1]) << 12;
    
    if ( 1 == padding)
        buffer += base64_chars.find(encodedBlock[2]) << 6;
    return buffer;
    }

/********************************************************************************/
string Base64Decoder::DecodePaddedBuffer(uint32_t buffer, uint8_t padding)
    {
    string decodedBUffer = "";
    decodedBUffer.append(1, (buffer & 0x00FF0000) >> 16);
    
    if (2 >= padding)
       decodedBUffer.append(1, (buffer & 0x0000FF00) >> 8);
    
    if (1 == padding) 
        decodedBUffer.append(1, (buffer & 0x000000FF) >> 0);
    return decodedBUffer;
    }

/********************************************************************************/
/* This method splits the decoding into two steps:                              */
/*    -  Decoding the valid encoded string in chunks                            */
/*    -  Decoding the last 4 symbols, that might contain padding                */
/*                                                                              */
/* I am not very satisfied with this implemantation as it 'feels' it could be   */
/* elegant. However this implementation provides what most online               */
/* solutions lack:                                                              */
/*    - It does not check each and every symbol not to be padding,              */
/*      which, privided the input is relatively long,                           */
/*      might impact performance sligthly.                                      */
/*    - It is far easier to debug and maintain, when compared to bitwise shits  */
/*      of 2-4 bits                                                             */
/********************************************************************************/
string Base64Decoder::Decode(string encodedString)
    {
    string   decodedString = "";
    
    if (!ValidateSring(encodedString))
        return decodedString;
    
    uint32_t length         = encodedString.length();
    uint32_t paddingPos     = encodedString.find("=", length - 3);
    uint8_t  paddingSymbols = 0; (-1 == paddingPos) ? 0 : length - paddingPos;

    if (-1 != paddingPos)
        {
        paddingSymbols = length - paddingPos;
        length = paddingPos;
        }
  
    // Handles the majority of decoding
    uint32_t fullBlocks = length / 4;
    for (int i = 0; i < fullBlocks; i++)
        { 
        uint32_t buffer = FillBuffer(encodedString.substr(i * 4, 4));
        decodedString.append(DecodeBuffer(buffer));
        }
    
    // Handles the decoding of padded string
    if (paddingSymbols > 0)
        {
        string   paddedString = encodedString.substr(fullBlocks * 4, 4);
        uint32_t paddedBuffer = FillPaddedBuffer(paddedString, paddingSymbols);
        decodedString.append(DecodePaddedBuffer(paddedBuffer, paddingSymbols));
        }

    return decodedString;
    }
/********************************************************************************/
