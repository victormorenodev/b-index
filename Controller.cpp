#include "Controller.h"
#include "DirOps.h"
#include "BOps.h"


void Controller::setRoot(int root){
    this->root = root;
}

int Controller::getRoot() {
    return root;
}

    
int Controller::getNpts() {
    return nPts;
}

void Controller::setNpts(int nPts) {
    this->nPts = nPts;
}

void Controller::doFLH(){
    setNpts(DirOps::readInLine(1).getX());
    DirOps::writeOutLine("FLH/"+to_string(getNpts()));
    //cout << DirOps::readInLine(1).getX();
}

void Controller::doINC(int x){
    if(x>0){
        int id = 0;
        int line = 0;

        for (int i=1; i<=1000; i++){                    // percorre o csv
            cout << " LINHA: " << to_string(i) << " , ";
            id = DirOps::readCSVLine(i, x);             // recebe o id da linha se o registro tem ano == x
            cout << " ID: " << to_string(id) << endl;
            if (id == -1){continue;}                  // pula pro próximo laço se o viho acessa do tem ao != de x
            line = BOps::posKey(x, getNpts(), getRoot());                     // recebe a posição que o nó deve ser inserido a árvore
            if(line == -1){
                BOps::rooteNode(x, id , getNpts());
                continue;
            }
            cout << "Entra e o line é esse = " << to_string(line) << endl;
            BOps::insertKey(x, id, line, getNpts());               // insere have no nó da liha line(nó da árvore)
            cout << "Sai" << endl;
        }
    }
    DirOps::writeOutLine("INC:"+to_string(x)+"/"+to_string(BOps::searchKey(x, getNpts())));
}

void Controller::doBUS(int x){
    int found = -1;
    if(x>0){
        found = BOps::searchKey(x, getNpts());
    }
    DirOps::writeOutLine("BUS:"+to_string(x)+"/"+to_string(found));
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
            doFLH();
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

Operation Controller::nextLine(int i) {
    return DirOps::readInLine(i);
}

Controller::Controller(int nPts) : nPts(nPts) {};