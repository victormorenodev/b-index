#include "BOps.h"
#include "DirOps.h"
#include "Structures.h"
#include <optional>
#include <algorithm>
using namespace std;

void BOps::rooteNode(int key, int id, int nPts){
    LeafNode* root = new LeafNode(-1, -1, nPts, -1);
    int line = DirOps::writeBTreeLine(root);
    
}

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

void BOps::splitNode(int line, int nPts, int key, int id){
    Node* node = DirOps::readBTreeLine(line, nPts);
    if(node->isLeaf()){BOps::splitLeaf(line,nPts,key,id);}
    else{BOps::splitInternal(line,nPts,key,id);}
    return;
}

void BOps::splitLeaf(int line, int nPts, int key, int id){
    Node* node = DirOps::readBTreeLine(line, nPts);
    LeafNode* leaf = dynamic_cast<LeafNode*>(node);
    vector<int>& keys = leaf->getKeys();
    vector<int>& csvpos = leaf->getCsvPos();
    int neighbor = leaf->getNeighbor();

    // Inserir nova chave temporariamente
    keys.push_back(key);
    csvpos.push_back(id);

    // Organizar pares chave-id
    vector<pair<int, int>> temp;
    for (size_t i = 0; i < keys.size(); ++i)
        temp.push_back({keys[i], csvpos[i]});

    sort(temp.begin(), temp.end());

    // Calcular mediana
    int medianIndex = temp.size() / 2;
    int medianKey = temp[medianIndex].first;
    int medianId = temp[medianIndex].second;

    // Inserir no pai
    insertKey(medianKey, -1, leaf->getFatherLine(), nPts);

    // Criar novo nó
    LeafNode* newleaf = new LeafNode(-1, leaf->getFatherLine(), nPts, neighbor);

    // Dividir dados
    leaf->getKeys().clear();
    leaf->getCsvPos().clear();
    newleaf->getKeys().clear();
    newleaf->getCsvPos().clear();

    for (int i = 0; i < medianIndex; ++i) {
        leaf->getKeys().push_back(temp[i].first);
        leaf->getCsvPos().push_back(temp[i].second);
    }

    for (size_t i = medianIndex; i < temp.size(); ++i) {
        newleaf->getKeys().push_back(temp[i].first);
        newleaf->getCsvPos().push_back(temp[i].second);
    }


    int newline = DirOps::writeBTreeLine(newleaf);
    leaf->setNeighbor(newline);
    DirOps::writeBTreeLine(leaf);
}

void BOps::splitInternal(int line, int nPts, int key, int id) {
    Node* node = DirOps::readBTreeLine(line, nPts);
    InternalNode* internal = dynamic_cast<InternalNode*>(node);

    std::vector<int>& keys = internal->getKeys();
    std::vector<int>& children = internal->getChildren();

    // Insere nova chave e filho temporariamente
    keys.push_back(key);
    children.push_back(id);

    // Agrupa chave com seu filho direito para ordenar
    std::vector<std::pair<int, int>> keyChildPairs;
    for (size_t i = 0; i < keys.size(); ++i) {
        keyChildPairs.emplace_back(keys[i], children[i + 1]);
    }

    // Ordena as chaves e filhos pela chave
    std::sort(keyChildPairs.begin(), keyChildPairs.end());

    // Reconstrói keys e children ordenados
    std::vector<int> orderedKeys;
    std::vector<int> orderedChildren;
    orderedChildren.push_back(children[0]); // filho esquerdo da primeira chave

    for (const auto& [k, ch] : keyChildPairs) {
        orderedKeys.push_back(k);
        orderedChildren.push_back(ch);
    }

    // Calcula índice da mediana
    int medianIndex = orderedKeys.size() / 2;
    int medianKey = orderedKeys[medianIndex];

    // Cria novo nó interno (novo irmão à direita)
    InternalNode* newInternal = new InternalNode(-1, internal->getFatherLine(), nPts);

    // Passa metade direita (chaves e filhos após mediana) para o novo nó
    for (size_t i = medianIndex + 1; i < orderedKeys.size(); ++i) {
        newInternal->getKeys().push_back(orderedKeys[i]);
    }
    for (size_t i = medianIndex + 1; i < orderedChildren.size(); ++i) {
        newInternal->getChildren().push_back(orderedChildren[i]);
    }

    // Atualiza o nó original com metade esquerda (antes da mediana)
    internal->getKeys().clear();
    internal->getChildren().clear();

    for (int i = 0; i < medianIndex; ++i) {
        internal->getKeys().push_back(orderedKeys[i]);
    }
    for (int i = 0; i <= medianIndex; ++i) {
        internal->getChildren().push_back(orderedChildren[i]);
    }

    // Escreve novo nó interno e obtém linha dele
    int newLine = DirOps::writeBTreeLine(newInternal);

    // Atualiza filhos para apontar para o pai correto (linha do pai será decidida abaixo)
    for (int childLine : internal->getChildren()) {
        Node* childNode = DirOps::readBTreeLine(childLine, nPts);
        childNode->setFatherLine(internal->getLine());
        DirOps::writeBTreeLine(childNode);
        delete childNode;
    }
    for (int childLine : newInternal->getChildren()) {
        Node* childNode = DirOps::readBTreeLine(childLine, nPts);
        childNode->setFatherLine(newLine);
        DirOps::writeBTreeLine(childNode);
        delete childNode;
    }

    // Verifica se o nó atual é raiz (linha 1)
    if (internal->getLine() == 1) {
        // Criar nova raiz na linha 1
        InternalNode* newRoot = new InternalNode(1, -1, nPts);
        newRoot->getKeys().push_back(medianKey);
        newRoot->getChildren().push_back(internal->getLine());
        newRoot->getChildren().push_back(newLine);

        // Atualiza fatherLine dos filhos da nova raiz
        internal->setFatherLine(1);
        newInternal->setFatherLine(1);

        // Escreve tudo no arquivo (sobrescrevendo raiz)
        DirOps::writeBTreeLine(internal);
        DirOps::writeBTreeLine(newInternal);
        DirOps::writeBTreeLine(newRoot);
    } else {
        // Nó tem pai, insere mediana no pai (recursivamente)
        internal->setFatherLine(internal->getFatherLine());
        newInternal->setFatherLine(internal->getFatherLine());
        DirOps::writeBTreeLine(internal);
        DirOps::writeBTreeLine(newInternal);

        insertKey(medianKey, newLine, internal->getFatherLine(), nPts);
    }
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
    if (node == NULL) {
        return -1;
    }
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
        splitNode(line, nPts, key, id);
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