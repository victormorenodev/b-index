#include "Structures.h"

Operation::Operation(Instruction o, int val) {
    instruction = o;
    x = val;
}

Instruction Operation::getInstruction() const {
    return instruction;
}

int Operation::getX() const {
    return x;
}