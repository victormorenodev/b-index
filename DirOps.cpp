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
        InternalNode* internalNode = new InternalNode(line, fatherLine, nPts, keys, children);
        return internalNode;
    }

    else {
        vector<int> csvPos = parseIntList(attributes[4]);
        int neighbor = stoi(attributes[5]);
        LeafNode* leafNode = new LeafNode(line, fatherLine, nPts, keys, csvPos, neighbor);
        return leafNode;
    }

}

string DirOps::parseNode(Node* node){
    int line = node->getLine();
    int fatherLine = node->getFatherLine();
    NodeType type = node->getType();
    vector<int> keys = node->getKeys();

    // InternalNode -> line:type:fatherLine:keys[]:children[] -> 2:INTERNAL:1:2001,2002:4,5
    // LeafNode -> line:type:fatherLine:keys[]:csvPos[]:neighbor -> 6:LEAF:4:2001,2002:8,12:7
    string result = "";
    result += to_string(line) + 
        ":" + 
        string(type == NodeType::INTERNAL ? "INTERNAL" : "LEAF") +
        ":" +
        to_string(fatherLine) + ":";
    for (int i = 0; i < keys.size(); i++) {
        result += to_string(keys[i]);
        if (i < keys.size()-1) {
            result += ", ";
        }
    }
    result += ":";
    if (type == NodeType::INTERNAL) {
        InternalNode* internalNode = dynamic_cast<InternalNode*>(node);
        vector<int> children = internalNode->getChildren();
        for (int i = 0; i < children.size(); i++) {
            result += to_string(children[i]);
            if (i < children.size()-1) {
                result += ", ";
            }
        }
    }
    else {
        LeafNode* leafNode = dynamic_cast<LeafNode*>(node);
        vector<int> csvPos = leafNode->getCsvPos();
        int neighbor = leafNode->getNeighbor();
        for (int i = 0; i < csvPos.size(); i++) {
            result += to_string(csvPos[i]);
            if (i < csvPos.size()-1) {
                result += ", ";
            }
        }
        result += ":"+to_string(neighbor);
    }
    return result;
}

Operation DirOps::readInLine(int line) { // 0 = INC, 1 = BUS, 2 = FLH
    ifstream in("in.txt");
    if (!in.is_open()) {
        cerr << "Erro ao abrir o arquivo in.txt" << endl;
        return Operation(Instruction::INVALID, -1);
    }
    string l;
    int currentLine = 1;
    while (getline(in, l) && currentLine < line) {
        currentLine++;
    }
    if (currentLine != line) {
        //cerr << "Essa linha não existe no arquivo in.txt" << endl;
        return Operation(Instruction::INVALID, -1);
    }
    cout << l.substr(0);
    if (l.substr(0, 1) == "I") {
        size_t colon = l.find(':');
        if (colon != string::npos) {
            return Operation(
                parseInstruction(l.substr(0, colon)), 
                stoi(l.substr(colon+1))
            );
        }
    } 
    else if (l.substr(0, 1) == "B") {
        size_t colon = l.find(':');
        if (colon != string::npos) {
            return Operation(
                parseInstruction(l.substr(0, colon-1)), 
                stoi(l.substr(colon+1))
            );
        }
    }
    else if (l.substr(0, 1) == "F"){
        size_t colon = l.find('/');
        if (colon != string::npos) {
            return Operation(
                parseInstruction(l.substr(0, colon)), 
                stoi(l.substr(colon+1))
            );
        }
    }
    cerr << "Formato de linha inválido" << endl;
    in.close();
    return Operation(Instruction::INVALID, -1);
}

int DirOps::parseCSVLine(string line){
    stringstream ss(line);
    string part;
    vector<string> attributes;

    while (getline(ss, part, ',')) {
        attributes.push_back(part);
    }

    if (attributes.size() != 4) {
        cerr << "Formato inválido de entrada do CSV!" << endl;
        return -1;
    }
    return stoi(attributes[2]);
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
        cerr << "Essa linha não existe no arquivo btree.txt" << endl;
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

int DirOps::writeBTreeLine(Node* node){
    ifstream inFile("btree.txt");
    int lineNumber = 1;
    string line;
    
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            lineNumber++;
        }
        inFile.close();
    }
    
    ofstream outFile("btree.txt", ios::app);
    
    if (!outFile.is_open()) {
        cerr << "Não foi possível abrir o arquivo btree.txt para escrita." << endl;
        return -1; 
    }
    
    string nodeString = parseNode(node);
    outFile << nodeString;
    
    outFile.close();
    
    return lineNumber;
}

void DirOps::writeOutLine(string line) {
    ofstream outFile("out.txt", ios::app);
    
    if (outFile.is_open()) {
        outFile << line << endl;
        
        outFile.close();
    } else {
        cerr << "Erro ao abrir ou gerar o arquivo out.txt" << endl;
    }
}

int DirOps::readCSVLine(int line, int x) {
    ifstream in("vinhos.csv");
    if (!in.is_open()) {
        cerr << "Erro ao abrir o arquivo vinho.csv" << endl;
        return -1;
    }
    string l;
    getline(in, l);
    int currentLine = 1;
    while (getline(in, l) && currentLine != line) {
        currentLine++;
    }
    if (currentLine != line) {
        cerr << "Essa linha não existe no arquivo vinhos.csv" << endl << line << endl;
        return -1;
    }
    in.close();
    if (parseCSVLine(l) != x) { return -1; };
    return parseCSVLine(l);
}

void nextLine(int i) {
    DirOps::readInLine(i);
}