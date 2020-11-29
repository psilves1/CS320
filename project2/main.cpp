#include <iostream>
#include <fstream>
#include <string>

#include "directMap.h"
#include "setAssociative.h"
#include "setAssocNoAlloc.h"
#include "prefetch.h"
#include "prefetchMiss.h"

int main(){

    std::ifstream infile("../traces/trace1.txt");

    std::string instructionType;
    unsigned long long addr;


    //1KB DirectMap set up
    #pragma region
    unsigned long long* cache1KB = new unsigned long long[32];
    int cacheHits1KB = 0;
    int cacheRequests1KB = 0;
    int val1KB = 0;
    #pragma endregion

    //4KB DirectMap Cache set up
    #pragma region
    unsigned long long* cache4KB = new unsigned long long[128];
    int cacheHits4KB = 0;
    int cacheRequests4KB = 0;
    int val4KB = 0;
    #pragma endregion

    //16KB DirectMap Cache set up
    #pragma region
    unsigned long long* cache16KB = new unsigned long long[512];
    int cacheHits16KB = 0;
    int cacheRequests16KB = 0;
    int val16KB = 0;
    #pragma endregion

    //32KB DirectMap Cache set up
    #pragma region
    unsigned long long* cache32KB = new unsigned long long[2048];
    int cacheHits32KB = 0;
    int cacheRequests32KB = 0;
    int val32KB = 0;
    #pragma endregion

    while (infile >> instructionType >> std::hex >> addr){
        
        //1KB DirectMap
        #pragma region 
        val1KB = directMap(instructionType, cache1KB, 1024, addr);
        cacheHits1KB += val1KB;
        cacheRequests1KB++;
        #pragma endregion

        //4KB DirectMap
        #pragma region
        val4KB = directMap(instructionType, cache4KB, 4096, addr);
        cacheHits4KB += val4KB;
        cacheRequests4KB++;
        #pragma endregion

        //16KB DirectMap
        #pragma region
        val16KB = directMap(instructionType, cache16KB, 16384, addr);
        cacheHits16KB += val16KB;
        cacheRequests16KB++;
        #pragma endregion

        //32KB DirectMap
        #pragma region
        val32KB = directMap(instructionType, cache32KB, 32768, addr);
        cacheHits32KB += val32KB;
        cacheRequests32KB++;
        #pragma endregion

    }

    infile.close();

    std::cout << cacheHits1KB << "," << cacheRequests1KB << "; ";
    std::cout << cacheHits4KB << "," << cacheRequests4KB << "; ";
    std::cout << cacheHits16KB << "," << cacheRequests16KB << "; ";
    std::cout << cacheHits32KB << "," << cacheRequests32KB << "; " << std::endl;

    //int setAssociative(unsigned long long** cache, int cacheSize, unsigned long long addr, int associativity);

    infile.open("../traces/trace1.txt");

    //2 way Assoc set up
    #pragma region
    unsigned long long** cache2 = new unsigned long long *[16384/2];
    for(int i = 0; i < 16384/2; i++){
        cache2[i] = new unsigned long long[2];
    }
    int cacheHits2waySet = 0;
    #pragma endregion

    //4 way Assoc set up
    #pragma region
    unsigned long long** cache4 = new unsigned long long *[16384/4];
    for(int i = 0; i < 16384/4; i++){
        cache4[i] = new unsigned long long[4];
    }
    int cacheHits4waySet = 0;
    #pragma endregion

    //8 way Assoc set up
    #pragma region
    unsigned long long** cache8 = new unsigned long long *[16384/8];
    for(int i = 0; i < 16384/8; i++){
        cache8[i] = new unsigned long long[8];
    }
    int cacheHits8waySet = 0;
    #pragma endregion

    //16 way Assoc set up
    #pragma region
    unsigned long long** cache16 = new unsigned long long *[16384/16];
    for(int i = 0; i < 16384/16; i++){
        cache16[i] = new unsigned long long[16];
    }
    int cacheHits16waySet = 0;
    #pragma endregion

    //Full Assoc set up
    #pragma region
    unsigned long long** cacheFull = new unsigned long long *[1];
    for(int i = 0; i < 1; i++){
        cacheFull[i] = new unsigned long long[16384/32];
    }
    int cacheHitsFullwaySet = 0;
    #pragma endregion


    while (infile >> instructionType >> std::hex >> addr){
        
        cacheHits2waySet += setAssociative(cache2, 16384/2, addr, 2);
        cacheHits4waySet += setAssociative(cache4, 16384/4, addr, 4);
        cacheHits8waySet += setAssociative(cache8, 16384/8, addr, 8);
        cacheHits16waySet += setAssociative(cache16, 16384/16, addr, 16);

        //using set associative algo for full associative question
        cacheHitsFullwaySet += setAssociative(cacheFull, 32, addr, 16384/32);
    }

    std::cout << cacheHits2waySet << "," << cacheRequests1KB << "; ";//<< std::endl;
    std::cout << cacheHits4waySet << "," << cacheRequests1KB << "; ";// << std::endl;
    std::cout << cacheHits8waySet << "," << cacheRequests1KB << "; ";
    std::cout << cacheHits16waySet << "," << cacheRequests1KB << ";" << std::endl;

    std::cout << cacheHitsFullwaySet << "," << cacheRequests1KB<< ";" << std::endl;
    std::cout << 0 << "," << cacheRequests1KB<< ";" << std::endl; //hot and cold place holder


    infile.close();


    //no alloc on write miss
    infile.open("../traces/trace1.txt");

    //2 way Assoc set up
    #pragma region
    unsigned long long** cache2NA = new unsigned long long *[16384/2];
    for(int i = 0; i < 16384/2; i++){
        cache2NA[i] = new unsigned long long[2];
    }
    int cacheHits2waySetNA = 0;
    #pragma endregion

    //4 way Assoc set up
    #pragma region
    unsigned long long** cache4NA = new unsigned long long *[16384/4];
    for(int i = 0; i < 16384/4; i++){
        cache4NA[i] = new unsigned long long[4];
    }
    int cacheHits4waySetNA = 0;
    #pragma endregion

    //8 way Assoc set up
    #pragma region
    unsigned long long** cache8NA = new unsigned long long *[16384/8];
    for(int i = 0; i < 16384/8; i++){
        cache8NA[i] = new unsigned long long[8];
    }
    int cacheHits8waySetNA = 0;
    #pragma endregion

    //16 way Assoc set up
    #pragma region
    unsigned long long** cache16NA = new unsigned long long *[16384/16];
    for(int i = 0; i < 16384/16; i++){
        cache16NA[i] = new unsigned long long[16];
    }
    int cacheHits16waySetNA = 0;
    #pragma endregion

    
    while (infile >> instructionType >> std::hex >> addr){
        
        cacheHits2waySetNA += setAssocNoAlloc(instructionType, cache2NA, 16384/2, addr, 2);
        cacheHits4waySetNA += setAssocNoAlloc(instructionType, cache4NA, 16384/4, addr, 4);
        cacheHits8waySetNA += setAssocNoAlloc(instructionType, cache8NA, 16384/8, addr, 8);
        cacheHits16waySetNA += setAssocNoAlloc(instructionType, cache16NA, 16384/16, addr, 16);

    }

    std::cout << cacheHits2waySetNA << "," << cacheRequests1KB << "; ";//<< std::endl;
    std::cout << cacheHits4waySetNA << "," << cacheRequests1KB << "; ";// << std::endl;
    std::cout << cacheHits8waySetNA << "," << cacheRequests1KB << "; ";
    std::cout << cacheHits16waySetNA << "," << cacheRequests1KB << ";" << std::endl;

    infile.close();


    infile.open("../traces/trace1.txt");

    //2 way Assoc set up
    #pragma region
    unsigned long long** cache2P = new unsigned long long *[16384/2];
    for(int i = 0; i < 16384/2; i++){
        cache2P[i] = new unsigned long long[2];
    }
    int cacheHits2waySetP = 0;
    #pragma endregion

    //4 way Assoc set up
    #pragma region
    unsigned long long** cache4P = new unsigned long long *[16384/4];
    for(int i = 0; i < 16384/4; i++){
        cache4P[i] = new unsigned long long[4];
    }
    int cacheHits4waySetP = 0;
    #pragma endregion

    //8 way Assoc set up
    #pragma region
    unsigned long long** cache8P = new unsigned long long *[16384/8];
    for(int i = 0; i < 16384/8; i++){
        cache8P[i] = new unsigned long long[8];
    }
    int cacheHits8waySetP = 0;
    #pragma endregion

    //16 way Assoc set up
    #pragma region
    unsigned long long** cache16P = new unsigned long long *[16384/16];
    for(int i = 0; i < 16384/16; i++){
        cache16P[i] = new unsigned long long[16];
    }
    int cacheHits16waySetP = 0;
    #pragma endregion

    while (infile >> instructionType >> std::hex >> addr){
        
        cacheHits2waySetP += prefetch(cache2P, 16384/2, addr, 2);
        cacheHits4waySetP += prefetch(cache4P, 16384/4, addr, 4);
        cacheHits8waySetP += prefetch(cache8P, 16384/8, addr, 8);
        cacheHits16waySetP += prefetch(cache16P, 16384/16, addr, 16);

    }

    std::cout << cacheHits2waySetP << "," << cacheRequests1KB << "; ";//<< std::endl;
    std::cout << cacheHits4waySetP << "," << cacheRequests1KB << "; ";// << std::endl;
    std::cout << cacheHits8waySetP << "," << cacheRequests1KB << "; ";
    std::cout << cacheHits16waySetP << "," << cacheRequests1KB << ";" << std::endl;

    infile.close();



    infile.open("../traces/trace1.txt");

    //2 way Assoc set up
    #pragma region
    unsigned long long** cache2PM = new unsigned long long *[16384/2];
    for(int i = 0; i < 16384/2; i++){
        cache2PM[i] = new unsigned long long[2];
    }
    int cacheHits2waySetPM = 0;
    #pragma endregion

    //4 way Assoc set up
    #pragma region
    unsigned long long** cache4PM = new unsigned long long *[16384/4];
    for(int i = 0; i < 16384/4; i++){
        cache4PM[i] = new unsigned long long[4];
    }
    int cacheHits4waySetPM = 0;
    #pragma endregion

    //8 way Assoc set up
    #pragma region
    unsigned long long** cache8PM = new unsigned long long *[16384/8];
    for(int i = 0; i < 16384/8; i++){
        cache8PM[i] = new unsigned long long[8];
    }
    int cacheHits8waySetPM = 0;
    #pragma endregion

    //16 way Assoc set up
    #pragma region
    unsigned long long** cache16PM = new unsigned long long *[16384/16];
    for(int i = 0; i < 16384/16; i++){
        cache16PM[i] = new unsigned long long[16];
    }
    int cacheHits16waySetPM = 0;
    #pragma endregion

    while (infile >> instructionType >> std::hex >> addr){
        
        cacheHits2waySetPM += prefetchMiss(cache2PM, 16384/2, addr, 2);
        cacheHits4waySetPM += prefetchMiss(cache4PM, 16384/4, addr, 4);
        cacheHits8waySetPM += prefetchMiss(cache8PM, 16384/8, addr, 8);
        cacheHits16waySetPM += prefetchMiss(cache16PM, 16384/16, addr, 16);

    }

    std::cout << cacheHits2waySetPM << "," << cacheRequests1KB << "; ";//<< std::endl;
    std::cout << cacheHits4waySetPM << "," << cacheRequests1KB << "; ";// << std::endl;
    std::cout << cacheHits8waySetPM << "," << cacheRequests1KB << "; ";
    std::cout << cacheHits16waySetPM << "," << cacheRequests1KB << ";" << std::endl;

    infile.close();


    return 0;
}