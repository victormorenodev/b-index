#ifndef CONTROLLER_H
#define CONTROLLER_H   

#include <iostream>
#include <fstream>
#include <sstream>
#include "Structures.h"

using namespace std;

class Controller {
    private:
        int nPts;
        void doFLH(int x); // passa o número máximo de filhos de cada nó para a bOps
        void doINC(int x); // insere um nó a árvore usando a bOps, passando um objeto de forma - (id(csv))
        void doBUS(int x); // recebe um chave de busca x, e descobre quantas chaves iguais existem na árvore
 
    public:
        void doOperation(Operation operation); // recebe uma operação e a partir do enum segue um fluxo
        int bTreeHeight(); // chama o método da classe bOps pra calcular a altura
        Controller(int nPts);
        int getNpts();
        void setNpts(int nPts);
};

#endif