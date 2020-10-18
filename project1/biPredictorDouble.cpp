#include <iostream>
#include <map>
#include <iterator>

#include "biPredictorDouble.h"
#include "table.h"

std::string biPredictorDouble(unsigned long long addr, std::string behavior,
                              unsigned long long target, Table *t)
{
    int numOfAddr = t->getNumOfAddr();
    int value = t->getCounterVal(addr % numOfAddr);
    // int bitSize = t->getBitSize();

    t->updateCounterVal(addr % numOfAddr, behavior);

    if (value > 1)
    {
        return "T";
    }
    return "NT";
}