#include <iostream>
#include <fstream>
#include <string>

#include "alwaysTaken.h"
#include "neverTaken.h"
#include "table.h"
#include "biPredictorSingle.h"
#include "biPredictorDouble.h"
#include "gshare.h"
#include "tournament.h"

int main(int argc, char *argv[])
{
    #pragma region initialize vars
    // Temporary variables
    unsigned long long addr;
    std::string behavior;
    unsigned long long target;

    // Open file for reading
    // TODO remove hardcoded file value later
    std::ifstream infile("../traces/short_trace1.txt");

    // number of correct predictions made by predictor
    unsigned long long correctPredictions[7] = {0,0,0,0,0,0,0};
    //   number of branches tested
    int branchesTested{0};
    #pragma endregion

    Table *t = new Table(1, 16, 1);
    Table *t2 = new Table(2, 16, 3);
    Table *t3 = new Table(2, 2048, 3);
    int ghr = 0;

    Table *t4 = new Table(2, 2048, 0); // tourny table
    Table *t5 = new Table(2, 2048, 3); //bimodial table
    Table *t6 = new Table(2, 2048, 3); //g-share table
    int ghr2 = 0;

    while (infile >> std::hex >> addr >> behavior >> std::hex >> target)
    {
        if (alwaysTaken(addr, behavior, target).compare(behavior) == 0)
        {
            correctPredictions[0]++;
        }

        if (neverTaken(addr, behavior, target).compare(behavior) == 0)
        {
            correctPredictions[1]++;
        }

        if (biPredictorSingle(addr, behavior, target, t).compare(behavior) == 0){
            correctPredictions[2]++;
        }

        if (biPredictorDouble(addr, behavior, target, t2).compare(behavior) == 0){
            correctPredictions[3]++;
        }
        
        if (gshare(addr, behavior, target, t3, ghr, 3).compare(behavior) == 0){
            correctPredictions[4]++;
        }
     
        if(tournamentPredictor(addr, behavior, target, t4, t5, t6, ghr2).compare(behavior) == 0){
            correctPredictions[5]++;
        }

        branchesTested++;
    }

    std::cout << correctPredictions[0] << std::endl;
    std::cout << correctPredictions[1] << std::endl;
    std::cout << correctPredictions[2] << std::endl;
    std::cout << correctPredictions[3] << std::endl;
    std::cout << correctPredictions[4] << std::endl;
    std::cout << correctPredictions[5] << std::endl;



    return 0;
}