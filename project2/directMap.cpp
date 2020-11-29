#include "directMap.h"

#include <string>
#include <cmath>
#include <iostream> 

int directMap(std::string instructionType, unsigned long long* cache, int cacheSize, unsigned long long addr){ 

    int addressSize = 64; //bits
    int byteOffsetBitSize = 5; //32 bytes, need 5 bits to give an index to each bit
    int cacheIndexBitSize = log2(cacheSize) - byteOffsetBitSize;
    int tagFieldBitSize = addressSize - (cacheIndexBitSize + byteOffsetBitSize);
    int numOfCacheLines = cacheSize / (1 << byteOffsetBitSize); //2^5

    /*
        1)get cache index
        2)store value at cache index value
    */

    unsigned long long index = (addr >> byteOffsetBitSize) & ((1 << (cacheIndexBitSize)) - 1);

    //removes first 5 bits, and every bit past the cacheBitIndex of addr

    // std::cout << "cache index bits size" << cacheIndexBitSize << std::endl;
    // std::cout << numOfCacheLines << std::endl;

    //2
    int tag = addr >> (cacheIndexBitSize + byteOffsetBitSize); // tag val
    int hit = (cache[index] == tag);
    cache[index] = tag;

    return hit; 
}