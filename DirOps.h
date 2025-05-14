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
        static string parseNode(Node node); // linha --> node
        static Node parseBTreeLine(string line); // node --> linha
        static int parseCSVLine(string line); // 
    public:
        static int readCSVLine(int line, int x); // retorna o id do vinho se x == ano, se n retorna -1
        static Operation readInLine(int line);
        static Node readBTreeLine(int line);
        static void deleteBTreeLine(int line);
        static void writeBTreeLine(Node node);
        static void writeOutLine(string line);
};

#endif