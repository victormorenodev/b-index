#ifndef CONTROLLER_H
#define CONTROLLER_H   

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
 
    public:
        static void doOperation(Operation operation); // recebe uma operação e a partir do enum segue um fluxo
        static int bTreeHeight(); // chama o método da classe bOps pra calcular a altura
};

#endif