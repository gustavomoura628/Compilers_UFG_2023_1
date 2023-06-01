#ifndef Lexico_hpp
#define Lexico_hpp

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <assert.h>
#include <vector>

#include "Token.hpp"

using namespace std;

class Lexico
{
    public:
        Lexico(string _pathFileProgramaFonte);
        ~Lexico();
        Token SCANNER();
        void imprimirTabelaSimbolos();
    private:
        void carregarPalavrasReservadas();
        void inserirTabelaSimbolos(Token token);
        void atualizarTabelaSimbolos(Token token);
        Token pesquisarTabelaSimbolos(string lexema);
        void excluirTabelaSimbolos(string lexema);
        void abrirProgramaFonte();
        void readNextCaracter();
        void carregarAutomato();
        void desfazerLeitura();

        string pathFilePalavrasReservadas = "Info/palavrasReservadas.txt";
        string pathFileAutomato = "Info/AutomatoLexico.txt";
        string pathFileProgramaFonte;

        set<Token> tabelaDeSimbolos;
        map<char, int> idxOfCaracter;
        vector<vector<int>> transicoesAutomato;
        map<int, string> estadosFinais, mensagensErro, tiposDosEstados;
        int linha, prev_coluna, coluna, estado;
        string buffer;
        char caracter;
        ifstream fileProgramaFonte;
};

#endif //Lexico_hpp
