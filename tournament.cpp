#include <iostream>
#include <map>
#include <iterator>

#include "tournament.h"
#include "table.h"

std::string tournamentPredictor(unsigned long long addr, std::string behavior,
                                unsigned long long target, Table *t, Table *biTable, Table *gTable,
                                int &ghr)
{
    int numOfAddr = t->getNumOfAddr();
    int value = t->getCounterVal(addr % numOfAddr);
    int gValue = gTable->getCounterVal((addr % numOfAddr) ^ ghr);
    int biValue = biTable->getCounterVal(addr % numOfAddr);

    if (value < 2)
    {
        value = gValue;
    }
    else
    {
        value = biValue;
    }


    if ((gValue >= 2) != (biValue >= 2)) //are their conclusions different?
    {
        if ((gValue >= 2) == (behavior.compare("T") == 0)) //is gValue correct?
        {                                               
            t->updateCounterVal(addr % numOfAddr, "NT"); //NT means -1 essentially
        }
        else
        {
            t->updateCounterVal(addr % numOfAddr, "T"); //T means +1 essentially
        }
    }

    biTable->updateCounterVal(addr % numOfAddr, behavior);
    gTable->updateCounterVal((addr % numOfAddr) ^ ghr, behavior);

    ghr <<= 1;
    ghr |= (behavior.compare("T") == 0);
    ghr %= (1 << 11);

    if (value > 1)
    {
        return "T";
    }
    return "NT";
}