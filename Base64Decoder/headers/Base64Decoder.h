#pragma once
#include <string>

class Base64Decoder
{
private:
    /*******************************************************************************/
    /* Validates encoded string:                                                   */
    /*     1) Minimal lengh                                                        */
    /*     2) Lengh modulus 4 check                                                */
    /*     3) Character set check                                                  */
    /*******************************************************************************/
    static bool ValidateSring(std::string const& encodedString);

    /*******************************************************************************/
    /* Decodes Base64 encoding using 24bit chunks, passed via 32 bit buffer        */
    /* Used for the unpadded part of the encoded string                            */
    /*******************************************************************************/
    static uint32_t FillBuffer(std::string const& encodedBlock);
    static std::string DecodeBuffer(uint32_t buffer);


    /*******************************************************************************/
    /* Decodes Base64 encoding using 24bit chunks, passed via 32 bit buffer        */
    /* Used for the padded part of the encoded string                              */
    /*******************************************************************************/
    static uint32_t FillPaddedBuffer(std::string const& encodedBlock, uint8_t padding);
    static std::string DecodePaddedBuffer(uint32_t buffer, uint8_t padding);

public:
    /*******************************************************************************/
    /* Decodes   Base64 encoded string.                                            */
    /* Input:    Base64 encoded string                                             */
    /* Output:   utf8   decoded string                                             */
    /* On Error: If provided input is invalid an empty string is returned          */
    /*******************************************************************************/
    /* Note: It is arguable if the input  should not be const&.                    */
    /*    - Having a copy is more costly but less likely to cause a crash          */
    /*    - Having move semantics makes encoded string unsuable afterwards         */
    /*      and might cause an inconvenience                                       */        
    /* Consideration for optimizing                                           */
    /*******************************************************************************/
    static std::string Decode(std::string encodedString);
};