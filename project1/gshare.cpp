#include <iostream>
#include <map>
#include <iterator>

#include "gshare.h"
#include "table.h"

std::string gshare(unsigned long long addr, std::string behavior,
                              unsigned long long target, Table *t, int &ghr, int ghrBitSize){
    
    int numOfAddr = t->getNumOfAddr();
    int value = t->getCounterVal((addr % numOfAddr) ^ ghr);

    t->updateCounterVal((addr % numOfAddr) ^ ghr, behavior);

    ghr <<= 1;
    ghr |= (behavior.compare("T") == 0);
    ghr %= (1 << ghrBitSize);

    if (value > 1)
    {
        return "T";
    }
    return "NT";
}