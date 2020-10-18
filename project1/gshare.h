#ifndef GSHARE_H
#define GSHARE_H

#include "table.h"

std::string gshare(unsigned long long addr, std::string behavior,
                              unsigned long long target, Table *t, int &ghr, int ghrBitSize);


#endif