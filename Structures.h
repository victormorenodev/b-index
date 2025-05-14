#ifndef STRUCTURES_H
#define STRUCTURES_H

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

#endif