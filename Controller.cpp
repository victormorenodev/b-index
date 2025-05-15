#include "Controller.h"
#include "DirOps.h"
#include "BOps.h"

Controller::Controller(int nPts) {
    this->nPts = nPts;
}

int Controller::getNpts() {
    return nPts;
}

void Controller::setNpts(int nPts) {
    this->nPts = nPts;
}

void Controller::doFLH(int x){
    if(x>0){BOps::setFLH(x);}
}

void Controller::doINC(int x){
    if(x>0){
        int id = 0;
        int line = 0;

        for (int i=0; i<=1000; i++){                    // percorre o csv
            id = DirOps::readCSVLine(i, x);             // recebe o id da linha se o registro tem ano == x
            if (id == -1){continue;}                    // pula pro próximo laço se o viho acessa do tem ao != de x
            line = BOps::posKey(x, getNpts());                     // recebe a posição que o nó deve ser inserido a árvore
            BOps::insertKey(x, id, line, getNpts());               // insere have no nó da liha line(nó da árvore)
        }
    }
}

void Controller::doBUS(int x){
    if(x>0){BOps::searchKey(x, getNpts());}
}

void Controller::doOperation(Operation operation){
    Instruction instr = operation.getInstruction();
    int x = operation.getX();

    switch (instr) {
        case Instruction::INC:
            doINC(x);
            break;
        case Instruction::BUS:
            doBUS(x);
            break;
        case Instruction::FLH:
            doFLH(x);
            break;
        default:
            std::cerr << "Instrução inválida recebida.\n";
            break;
    }
}

int Controller::bTreeHeight(){
    int h = BOps::calcHeight(getNpts()); // calcula a altura da árvore
    return h;
}