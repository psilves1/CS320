#ifndef X
#define X

#include <string>
#include <map>

class Table{

public:
    Table();
    Table(int bitSize, int numOfAddr, int fieldVal);

    void addNewAddr(int address);
    int getCounterVal(int address);
    void updateCounterVal(int address, std::string prevResult);   
    int getNumOfAddr();
    void printTable();
    void printx();

private:
    int bitSize{};
    int numOfAddr{};
    int fieldVal{};
    std::map <int, int> map {};
    int *arr;
};

#endif // X