#ifndef DIROPS_H
#define DIROPS_H   

#include <iostream>
#include <fstream>
#include <sstream>
#include "Structures.h"

using namespace std;

class DirOps {
    private:
        static Instruction parseInstruction(string i);
    public:
        static Operation readInLine(int line);
};

#endif