#ifndef CONTROLLER_H
#define CONTROLER_H   

#include <iostream>
#include <fstream>
#include <sstream>
#include "Structures.h"

using namespace std;

class Controller {
    private:
        static void doFLH(int x); // passa o número máximo de filhos de cada nó para a bOps
        static void doINC(int x); // insere um nó a árvore usando a bOps, passando um objeto de forma - (id(csv))
        static void doBUS(int x); // recebe um chave de busca x, e descobre quantas chaves iguais existem na árvore

        static int readCSVLine(int year); // ler o csv, se o (ano == x) -> retorna o id desse vinho, senão retorna -1
        static Node readBtreeLine(int line); // ler uma linha da árvore e retorna um node;
        static void writeBtreeLine(Node node); // escreve um node na árvore;

        static void insertRegister(int id, int year); // insere um registro de ano year e posição id no csv
        static void splitNode(int line); //splita o nó na linha ile da árvore
 
    public:
        static void doOperation(Operation operation); // recebe uma operação e a partir do enum segue um fluxo
        static void bTreeHeight(); // chama o método da classe bOps pra calcular a altura
};

#endif