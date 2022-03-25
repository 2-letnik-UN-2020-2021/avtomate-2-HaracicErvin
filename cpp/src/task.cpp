#include <iostream>
#include <fstream>
#include "scanner.h"

int main(int argc, char** argv) 
{
    std::ifstream dato(argv[1]);

    if (dato.is_open()) {
        Scanner scan(&dato);
        while (!scan.currentToken().isEof()) {
            std::cout << scan.nextToken();
            std::cout << scan.nextToken();
        }
    }
}
