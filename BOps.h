#ifndef BOPS_H
#define BOPS_H   

#include <iostream>
#include <fstream>
#include <sstream>
#include "Structures.h"

using namespace std;

class BOps {
    private:
        static std::optional<Node> readBtreeLine(int line); // ler uma linha da árvore e retorna um node;
        static void writeBtreeLine(Node node); // escreve um node na árvore;
        static void splitNode(int line); // splita o nó da linha informada
        static int countKey(int line); // a partir de uma folha ele conta quantas vezes uma chave se repete na árvore
    public:
        static int posKey(int key); // acha a folha que essa chave deve ser inserida, retorna a linha dessa folha
        static void insertKey(int key, int id, int line); // insere uma chave no nó de linha "line"
        static int searchKey(int key); // retorna o número de chaves tal que chave == key
        static int calcHeight(); // calcula a altura da árvore
        static void setFLH(int flh); // setar o máximo de filhos por nó
};

#endif