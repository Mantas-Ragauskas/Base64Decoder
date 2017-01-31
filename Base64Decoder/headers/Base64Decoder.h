#pragma once
#include <String>

using std::string;

class Base64Decoder
{
private:
    /*******************************************************************************/
    /* Found this idea of encoded character to integer conversion                  */
    /* on http://www.adp-gmbh.ch/cpp/common/base64.html                            */
    /*          (original code by René Nyffenegger)                                */
    /*                                                                             */
    /* Moved character resolution from in-loop to character resolution thus        */
    /* having same performance, a bit more code lines, but far greater readability */ 
    /*                                                                             */
    /* As a consequence i had to wrap std::string::find to result 0 instead of -1  */
    /* Optimizing for performance this method could be rewritten                   */ 
    /* to accualy override rather than wrap the find function                      */
    /*******************************************************************************/
    static const string base64_chars;

private:
    /*******************************************************************************/
    /* Wraps std:string:find fuction for search in base64_chars alphabet           */
    /* Input:    Valid Base64 character                                            */
    /* Output:   Integer representation of input                                   */
    /* On Error: If the symbol is not recognized 0 is returned                     */             
    /* Note:   Value 0 is ambigous with symbol A. As such this method              */
    /*         cannot be used for Base64 validation                                */        
    /*******************************************************************************/
    static uint8_t DecodeBase64Character(char encodedCharacter);

    /*******************************************************************************/
    /* Validates encoded string:                                                   */
    /*     1) Minimal lengh                                                        */
    /*     2) Lengh modulus 4 check                                                */
    /*     3) Character set check                                                  */
    /*******************************************************************************/
    static bool ValidateSring(const string& encodedString);

    /*******************************************************************************/
    /*                                                                             */
    /*******************************************************************************/
    static uint32_t FillBuffer(const string& encodedBlock);
    
    /*******************************************************************************/
    /*                                                                             */
    /*******************************************************************************/
    static string DecodeBuffer(uint32_t buffer);

public:
    /*******************************************************************************/
    /* Decodes   Base64 encoded string.                                            */
    /* Input:    Base64 encoded string                                             */
    /* Output:   utf8   decoded string                                             */
    /* On Error: If provided input is invalid an empty string is returned          */
    /*******************************************************************************/
    /* Note: It is arguable if the input  should not be const&.                    */
    /*      Having a copy is more costly but less likely to cause a crash          */
    /*      Consideration for optimizing                                           */
    /*******************************************************************************/
    static string Decode(string encodedString);
};