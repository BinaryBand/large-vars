#include "./src/datatypes/integer.h"
#include <iostream>
using namespace std;


string bin(Word w) {
    string out = "";
    int length = w.getSize();
    
    for (int i = 0; i < length; i++) {
        char byte = w.bytes[i];
        for (int j = 0; j < 8; j++) {
            out += (byte & 0b10000000 ? '1' : '0');
            byte <<= 1;
        }
    }

    return out;
}

int main(int argc, char* argv[]) {
    Integer seven = 7;
    Integer twelve = 12;
    Integer nineteen = 7 + 12;

    cout << bin(seven) << ' ' << seven << endl;
    cout << bin(twelve) << ' ' << twelve << endl;
    cout << bin(nineteen) << ' ' << nineteen << endl;

    twelve = 19 - 7;
    cout << bin(twelve) << ' ' << twelve << endl;

    Integer negative = 7 - 19;
    cout << bin(negative) << ' ' << negative << endl;

    return 0;
}