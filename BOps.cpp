#include "BOps.h"
#include "DirOps.h"
#include <optional>
#include "Structures.cpp"

std::optional<Node> Node BOps::readBtreeLine(int line){
    if(line != NULL && line>0){
    Node node = DirOps::readBTreeLine(line);
    return node;
    }
    return std::nullopt; // linha inválida
}

void BOps::writeBtreeLine(Node node){

}

void BOps::splitNode(int line){
}

int BOps::countKey(int line){
}

int BOps::posKey(int key){
}

void BOps::insertKey(int key, int id, int line){
}

int BOps::searchKey(int key){
}

int BOps::calcHeight(){
}