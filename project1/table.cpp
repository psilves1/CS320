#include "table.h"

#include <iostream>
#include <map>
#include <iterator>
#include <string>

Table::Table(int bitSize, int numOfAddr, int fieldVal)
{
    this->bitSize = bitSize;
    this->numOfAddr = numOfAddr;
    this->fieldVal = fieldVal;
    this->arr = new int[numOfAddr];
}

void Table::addNewAddr(int address)
{
    // for (int i = numOfAddr - 1; i > 0; i--)
    // {
    //     arr[i] = arr[i - 1]; //shift all values further into the list
    // }

    // arr[0] = address;

    map.insert(std::pair<int, int>(address, fieldVal));
}

int Table::getCounterVal(int address)
{
    std::map<int, int>::iterator it = map.find(address);

    if (it != map.end())
    {
        return (*it).second;
    }

    addNewAddr(address);
    return fieldVal;
}

void Table::updateCounterVal(int address, std::string prevResult)
{
    if (bitSize == 1)
    {
        if (prevResult.compare("NT") == 0)  // if prev result is NT
        {
            map.find(address)->second = 0;
        }
        else if (prevResult.compare("T") == 0) //if prev result is T
        {
            map.find(address)->second = 1;
        }
    }
    else
    {
        if (map.find(address)->second < 3 && prevResult.compare("T") == 0)
        {
            map.find(address)->second += 1;

        }
        else if (map.find(address)->second > 0 && prevResult.compare("NT") == 0)
        {
            map.find(address)->second -= 1;

        }
    }
}

int Table::getNumOfAddr()
{
    return numOfAddr;
}

void Table::printTable()
{
    std::map<int, int>::iterator it;

    for (it = map.begin(); it != map.end(); it++)
    {
        std::cout << it->first // string (key)
                  << ':'
                  << it->second // string's value
                  << std::endl;
    }
}


