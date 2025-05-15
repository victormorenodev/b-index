#include "DirOps.h"

Instruction DirOps::parseInstruction(string i) {
    if (i == "INC") return Instruction::INC;
    else if (i == "BUS") return Instruction::BUS;
    else if (i == "FLH") return Instruction::FLH;
    else return Instruction::INVALID;
}

NodeType parseNodeType(string str) {
    if (str == "INTERNAL") return NodeType::INTERNAL;
    if (str == "LEAF") return NodeType::LEAF;
    throw invalid_argument("Tipo de nó inválido!");
}

vector<int> parseIntList(string str) {
    vector<int> result;
    stringstream ss(str);
    string item;

    while (getline(ss, item, ',')) {
        result.push_back(stoi(item));
    }

    return result;
}

// InternalNode -> line:type:fatherLine:keys[]:children[] -> 2:INTERNAL:1:2001,2002:4,5
// LeafNode -> line:type:fatherLine:keys[]:csvPos[]:neighbor -> 6:LEAF:4:2001,2002:8,12:7
Node* DirOps::parseBTreeLine(string treeLine, int nPts){
    stringstream ss(treeLine);
    string part;
    vector<string> attributes;

    while (getline(ss, part, ':')) {
        attributes.push_back(part);
    }

    if (attributes.size() != 5 && attributes.size() != 6) {
        cerr << "Formato inválido de Node!" << endl;
        return NULL;
    }

    int line = stoi(attributes[0]);
    NodeType type = parseNodeType(attributes[1]);
    int fatherLine = stoi(attributes[2]);
    vector<int> keys = parseIntList(attributes[3]);

    if (type == NodeType::INTERNAL) {
        vector<int> children = parseIntList(attributes[4]);
        return NULL;
    }

    else {
        vector<int> csvPos = parseIntList(attributes[4]);
        int neighbor = stoi(attributes[5]);
        return NULL;
    }

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
    in.close();
    return Operation(Instruction::INVALID, -1);
}

string DirOps::parseNode(Node* node){
    return "";
}

int DirOps::parseCSVLine(string line){
    return -1;
}

Node* DirOps::readBTreeLine(int line, int nPts){
    ifstream in("btree.txt");
    if (!in.is_open()) {
        cerr << "Erro ao abrir o arquivo btree.txt" << endl;
        return NULL;
    }
    string l;
    int currentLine = 0;
    while (getline(in, l) && currentLine != line) {
        currentLine++;
    }
    if (currentLine != line) {
        cerr << "Essa linha não existe no arquivo in.txt" << endl;
        return NULL;
    }
    in.close();
    return parseBTreeLine(l, nPts);
}

void DirOps::editBTreeLine(int line, Node* newNode){
    ifstream inFile("btree.txt");
    ofstream outFile("temp.txt");

    if (!inFile || !outFile) {
        cerr << "Erro ao abrir arquivos!" << endl;
        return;
    }

    string bufferLine;
    int currentLine = 1;

    while(getline(inFile, bufferLine)) {
        if (currentLine == line) {
            outFile << parseNode(newNode) << "\n";
            currentLine++;
            continue;
        }
        outFile << bufferLine << "\n";
        currentLine++;
    }

    inFile.close();
    outFile.close();

    remove("btree.txt");
    rename("temp.txt", "btree.txt");
}

void DirOps::writeBTreeLine(Node* node){
}

void DirOps::writeOutLine(string line){
}

int DirOps::readCSVLine(int line, int x) {
    return -1;
}