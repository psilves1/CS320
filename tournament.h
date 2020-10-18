#ifndef tourny
#define tourny

#include "table.h"


std::string tournamentPredictor(unsigned long long addr, std::string behavior,
                              unsigned long long target, Table *t, Table *biTable, Table *gTable,
                              int &ghr);
                              
#endif // tourny