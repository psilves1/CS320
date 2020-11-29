#include "setAssocNoAlloc.h"
#include "setAssociative.h"

#include <string>
#include <cmath>
#include <iostream>

int setAssocNoAlloc(std::string instructionType, unsigned long long **cache, int cacheSize, unsigned long long addr, int associativity)
{

    int addressSize = 64;                                        //bits
    int byteOffsetBitSize = 5;                                   //32 bytes, need 5 bits to give an index to each bit
    int cacheIndexBitSize = log2(cacheSize) - byteOffsetBitSize; //cache size is the number of sets in the cache
    int tagFieldBitSize = addressSize - (cacheIndexBitSize + byteOffsetBitSize);
    int numOfCacheLines = cacheSize / (1 << byteOffsetBitSize); //2^5

    unsigned long long index = (addr >> byteOffsetBitSize) & ((1 << (cacheIndexBitSize)) - 1);

    int tag = addr >> (cacheIndexBitSize + byteOffsetBitSize); // tag val

    int indexOfTag = -1;

    for (int i = 0; i < associativity; i++)
    {
        if (cache[index][i] == tag)
        {
            indexOfTag = i;
            break;
        }
    }

    //if instruction is a store, then do not store in the cache
    if (instructionType.compare("L") == 0 || indexOfTag > -1)
    {
        if (indexOfTag == -1)
        {
            shuffle(cache[index], associativity); //shuffles every tag in the set down one position
            cache[index][0] = tag;
        }
        else
        {
            shuffle2(cache[index], associativity, indexOfTag); //shuffles every tag down one postion
                                                               // if that tag was above the "good" tag
            cache[index][0] = tag;
        }
    }

    // std::cout << "got here" << std::endl;

    return (indexOfTag != -1); //if it was in the cache, then we have an index >-1 and will return 1
}