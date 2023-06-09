#include <iostream>

#include "Token.hpp"
#include "Lexico.hpp"
#include "SymbolTable.hpp"

using namespace std;

int main(int argc, char *argv[]){

    Token t;
    string path_to_source_code = argv[1];
    SymbolTable tabelaDeSimbolos;
    Lexico l(path_to_source_code, tabelaDeSimbolos);
    do
    {
        t = l.SCANNER();
        if (t.getClasse() != "ERRO")
            cout << t << endl;
    } while (t.getClasse() != "EOF");
    tabelaDeSimbolos.imprimir();
    return 0;
}
