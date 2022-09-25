#include <iostream>
#include "./src/datatypes/integer.h"


int main(int argc, char* argv[]) {
    Integer twelve = 12;
    Integer seven = 7;

    cout << twelve.toBin() << endl;
    cout << seven.toBin() << endl;

    twelve += seven;
    cout << twelve.toBin() << endl;
    
    return 0;
}