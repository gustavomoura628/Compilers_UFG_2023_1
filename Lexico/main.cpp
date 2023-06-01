#include <iostream>

#include "Token.hpp"
#include "Lexico.hpp"

using namespace std;

int main(int argc, char *argv[]){

    Token t;
    string path_to_source_code = argv[1];
    Lexico l(path_to_source_code);
    do
    {
        t = l.SCANNER();
        if (t.getClasse() != "ERRO")
            cout << t << endl;
    } while (t.getClasse() != "EOF");
    l.imprimirTabelaSimbolos();
    return 0;
}
