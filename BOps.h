#ifndef BOPS_H
#define BOPS_H   

#include <iostream>
#include <fstream>
#include <sstream>
#include "Structures.h"
#include <optional>

using namespace std;

class BOps {
    private:
        static optional<Node*> readBtreeLine(int line, int nPts); // ler uma linha da árvore e retorna um node;
        static void writeBtreeLine(Node* node); // escreve um node na árvore;
        static void splitNode(int line, int nPts, int key, int id); // splita o nó da linha informada
        static int countKey(int line, int key, int nPts); // a partir de uma folha ele conta quantas vezes uma chave se repete na árvore
        static void splitLeaf(int line, int nPts, int key, int id);
        static void splitInternal(int line, int nPts, int key, int id);
    public:
        static int posKey(int key, int nPts); // acha a folha que essa chave deve ser inserida, retorna a linha dessa folha
        static void insertKey(int key, int id, int line, int nPts); // insere uma chave no nó de linha "line"
        static int searchKey(int key, int nPts); // retorna o número de chaves tal que chave == key
        static int calcHeight(int nPts); // calcula a altura da árvore
        static void setFLH(int flh); // setar o máximo de filhos por nó
};

#endif