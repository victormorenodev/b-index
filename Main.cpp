#include "DirOps.h"

using namespace std;

int main() {
    Operation test = DirOps::readInLine(0);
    cout << test.getX() << endl;
    return 0;   
}