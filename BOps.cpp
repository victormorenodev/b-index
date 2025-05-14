#include "BOps.h"
#include "DirOps.h"
#include "Structures.h"
#include <optional>
using namespace std;

std::optional<Node*> BOps::readBtreeLine(int line){
    if(line>0){
    Node* node = DirOps::readBTreeLine(line); //definir se é leaf ou iternal detro do DirOps
    return node;
    }
    return std::nullopt; // linha inválida
}

void BOps::writeBtreeLine(Node* node){
    DirOps::writeBTreeLine(node); // tratar no DirOps os casos de ser leaf ou iternal
}

void BOps::splitNode(int line){
}

int BOps::countKey(int line, int key){
    Node* node = DirOps::readBTreeLine(line);
    LeafNode* leaf = dynamic_cast<LeafNode*>(node);
    int count = 0;
    const vector<int>* keys = &leaf->getKeys();
    
    int i = 0;
    while((*keys)[i] == -1 || (*keys)[i] == key){
        if (key == (*keys)[i]){count++;}
        i++;
        if(i>(keys->size()-1)){
            i = 0;
            if (leaf->getNeighbor() > 0){
            node = DirOps::readBTreeLine(leaf->getNeighbor());
            leaf = dynamic_cast<LeafNode*>(node);
            keys = &leaf->getKeys();}
            else{break;}
        }
    }
    return count;
}

int BOps::posKey(int key){
}

void BOps::insertKey(int key, int id, int line){
}

int BOps::searchKey(int key){
    int line = posKey(key);
    int count = countKey(line, key);
    return count;
}

int BOps::calcHeight(){
    //desce na árvore e conta os loops, ou armazena o número de nós e calcula a altura com uma equação
}