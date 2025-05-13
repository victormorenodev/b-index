#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {

    // enum da Instrução
    enum class Instruction {
        INC,
        BUS,
        INVALID
    };
    
    // Operation (INSTRUÇÃO|X)
    class Operation {
    private:
        Instruction instruction;
        int x;
    public:
        Operation(Instruction o, int val) {
            instruction = o;
            x = val;
        }
        Instruction getInstruction() { return instruction; };
        int getX() { return x; };
    };

    // classe DirOps com todos os métodos de manipulação de diretório
    class DirOps {
    private:
        static Instruction parseInstruction(string i) {
            if (i == "INC") return Instruction::INC;
            else if (i == "BUS") return Instruction::BUS;
            else return Instruction::INVALID;
        }
    public:
        // lê uma linha do in.txt e retorna a Operation
        static Operation readInLine(int line) {
            ifstream in("in.txt");
            if (!in.is_open()) {
                cerr << "Erro ao abrir o arquivo in.txt" << endl;
                return Operation(Instruction::INVALID, -1);
            }
            string l;
            int currentLine = 0;
            while (getline(in, l) && currentLine != line) {
                currentLine++;
            }
            if (currentLine != line) {
                cerr << "Essa linha não existe no arquivo in.txt" << endl;
                return Operation(Instruction::INVALID, -1);
            }
            size_t colon = l.find(':');
            if (colon != string::npos) {
                return Operation(
                    parseInstruction(l.substr(0, colon)), 
                    stoi(l.substr(colon+1))
                );
            }
            cerr << "Formato de linha inválido" << endl;
            return Operation(Instruction::INVALID, -1);
        }
    };

    Operation test = DirOps::readInLine(1);
    cout << test.getX() << endl;
    return 0;   
}