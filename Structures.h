#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>

using namespace std;

enum class Instruction {
    INC,
    BUS,
    INVALID
};

class Operation {
    private:
        Instruction instruction;
        int x;

    public:
        Operation(Instruction o, int val);

        Instruction getInstruction() const;

        int getX() const;
    };

class Node {

    enum Type {
        INTERNAL, 
        LEAF
    };

    private:
        int line;
        int nPts;
        Type type;
        int fatherLine;
        vector<int> keys;
        vector<int> csvPos;
        vector<int> pts;

    public:
        // respectivamente: linha na árvore, número máximo de ponteiros, tipo do nó, linha do pai na árvore, vetor de chaves,
        // posição das chaves no csv e vetor de ponteiros
        Node(int line, int nPts, Type type, int fatherLine, int firstKey, vector<int> keys, vector<int> csvPos, vector<int> pts);
};

#endif