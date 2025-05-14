#include "DirOps.h"

Instruction DirOps::parseInstruction(string i) {
    if (i == "INC") return Instruction::INC;
    else if (i == "BUS") return Instruction::BUS;
    else return Instruction::INVALID;
}

Operation DirOps::readInLine(int line) {
    ifstream in("in.txt");
    if (!in.is_open()) {
        cerr << "Erro ao abrir o arquivo in.txt" << endl;
        return Operation(Instruction::INVALID, -1);
    }
    string l;
    int currentLine = 0;
    while (getline(in, l) && currentLine != line) {
        currentLine++;
    }
    if (currentLine != line) {
        cerr << "Essa linha não existe no arquivo in.txt" << endl;
        return Operation(Instruction::INVALID, -1);
    }
    size_t colon = l.find(':');
    if (colon != string::npos) {
        return Operation(
            parseInstruction(l.substr(0, colon)), 
            stoi(l.substr(colon+1))
        );
    }
    cerr << "Formato de linha inválido" << endl;
    return Operation(Instruction::INVALID, -1);
}

string DirOps::parseNode(Node node){
}

Node DirOps::parseBTreeLine(string line){
}

int DirOps::parseCSVLine(string line){
}

Operation DirOps::readInLine(int line){
}

Node DirOps::readBTreeLine(int line){
}

void DirOps::deleteBTreeLine(int line){
}

void DirOps::writeBTreeLine(Node node){
}

void DirOps::writeOutLine(string line){
}