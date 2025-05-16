#include "Controller.h"
#include "Structures.h"
#include "DirOps.h"

using namespace std;

int main() {
    Controller* controller = new Controller(-1);
    //Operation* operation = new Operation(Instruction::FLH, -1);
    //controller->doOperation(*(operation));
    controller->doOperation(controller->nextLine(1));
    controller->doOperation(controller->nextLine(2));
    int i = 0;
    /*do {
        i++;
        controller->doOperation(controller->nextLine(i));
    } while(controller->nextLine(i+1).getInstruction() != Instruction::INVALID);*/
    return 0;   
}