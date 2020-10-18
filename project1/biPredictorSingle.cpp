#include <iostream>
#include <map>
#include <iterator>

#include "biPredictorSingle.h"
#include "table.h"

std::string biPredictorSingle(unsigned long long addr, std::string behavior,
                              unsigned long long target, Table *t)
{

    int numOfAddr = t->getNumOfAddr();
    int value = t->getCounterVal(addr % numOfAddr);

    t->updateCounterVal(addr % numOfAddr, behavior);

    if (value == 1)
    {
        return "T";
    }
    return "NT";
}
