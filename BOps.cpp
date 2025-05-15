#include "BOps.h"
#include "DirOps.h"
#include "Structures.h"
#include <optional>
using namespace std;

optional<Node*> BOps::readBtreeLine(int line, int nPts){
    if(line>0){
    Node* node = DirOps::readBTreeLine(line, nPts); //definir se é leaf ou iternal detro do DirOps
    return node;
    }
    return nullopt; // linha inválida
}

void BOps::writeBtreeLine(Node* node){
    DirOps::writeBTreeLine(node); // tratar no DirOps os casos de ser leaf ou iternal
}

void BOps::splitNode(int line){
    //
    return;
}

int BOps::countKey(int line, int key, int nPts){
    Node* node = DirOps::readBTreeLine(line, nPts);
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
            node = DirOps::readBTreeLine(leaf->getNeighbor(), nPts);
            leaf = dynamic_cast<LeafNode*>(node);
            keys = &leaf->getKeys();}
            else{break;}
        }
    }
    return count;
}

int BOps::posKey(int key, int nPts) {
    Node* node = DirOps::readBTreeLine(1, nPts);

    // Enquanto não for folha, desce na árvore
    while (!node->isLeaf()) {
        InternalNode* internal = dynamic_cast<InternalNode*>(node);
        vector<int>& keys = internal->getKeys();
        vector<int>& children = internal->getChildren();

        int i = 0;
        for (; i < keys.size(); i++) {
            if (key < keys[i]) {
                break;  // Encontrei o filho correto
            }
        }

        // Desce para o filho escolhido
        node = DirOps::readBTreeLine(children[i], nPts);
    }

    // Quando chegar na folha, retorna a linha dela
    return node->getLine();
}

void BOps::insertKey(int key, int id, int line, int nPts) {
    Node* node = DirOps::readBTreeLine(line, nPts);
    LeafNode* leaf = dynamic_cast<LeafNode*>(node);
    vector<int>& keys = leaf->getKeys();
    vector<int>& csvpos = leaf->getCsvPos();

    if (keys[keys.size() - 1] != -1) {
        splitNode(line);
        return;  // encerra a função aqui
    }

    int swap_key = key;
    int swap_pos = id;

    for (int i = 0; i < keys.size(); i++) {
        if (keys[i] == -1 || keys[i] > swap_key) {
            swap(keys[i], swap_key);
            swap(csvpos[i], swap_pos);
        }
    }
}

int BOps::searchKey(int key, int nPts){
    int line = posKey(key, nPts);
    int count = countKey(line, key, nPts);
    return count;
}

int BOps::calcHeight(int nPts){
    Node* node = DirOps::readBTreeLine(1, nPts);
    InternalNode* internal = dynamic_cast<InternalNode*>(node);
    const vector<int>* children = &internal->getChildren();
    int h = 0;
    while (!internal->isLeaf()){
        node = DirOps::readBTreeLine((*children)[0], nPts);
        internal = dynamic_cast<InternalNode*>(node);
        children = &internal->getChildren();
        h++;
    }
    return h;
}