#include "Lexico.hpp"

Lexico::Lexico(string _pathFileProgramaFonte)
{
    pathFileProgramaFonte = _pathFileProgramaFonte;
    carregarPalavrasReservadas();
    abrirProgramaFonte();
    carregarAutomato();
}

Lexico::~Lexico()
{
    fileProgramaFonte.close();
    tabelaDeSimbolos.clear();
}

void Lexico::carregarPalavrasReservadas()
{
    ifstream file(pathFilePalavrasReservadas);
    assert(file.is_open());
    string palavraReservada;
    while (file >> palavraReservada)
    {
        Token tokenPalavraReservada(palavraReservada);
        inserirTabelaSimbolos(tokenPalavraReservada);
    }
    file.close();
}

void Lexico::inserirTabelaSimbolos(Token token)
{
    tabelaDeSimbolos.insert(token);
}

void Lexico::atualizarTabelaSimbolos(Token token)
{
    excluirTabelaSimbolos(token.getLexema());
    inserirTabelaSimbolos(token);
}

Token Lexico::pesquisarTabelaSimbolos(string lexema)
{
    auto tokenPtr = tabelaDeSimbolos.find(Token(lexema));
    if (tokenPtr == tabelaDeSimbolos.end())
        return Token();
    return *tokenPtr;
}

void Lexico::excluirTabelaSimbolos(string lexema)
{
    tabelaDeSimbolos.erase(Token(lexema));
}

void Lexico::abrirProgramaFonte()
{
    fileProgramaFonte.open(pathFileProgramaFonte);
    fileProgramaFonte >> noskipws;
    assert(fileProgramaFonte.is_open());
    prev_coluna = coluna = estado = 0;
    linha = 1;
    buffer.clear();
}

void Lexico::readNextCaracter()
{
    fileProgramaFonte >> caracter;
    prev_coluna = coluna;
    if (fileProgramaFonte.eof())
        caracter = EOF;
    if (caracter == '\n'){
        linha++;
        coluna = 0;
    }
    else
        coluna++;
}

void Lexico::desfazerLeitura()
{
    fileProgramaFonte.seekg(-1, fileProgramaFonte.cur);
    if (caracter == '\n') linha--;
    coluna = prev_coluna;
}

Token Lexico::SCANNER()
{
    int proximoEstado;
    bool error = false;
    do{
        readNextCaracter();

        proximoEstado = transicoesAutomato[estado][idxOfCaracter[caracter]];
        if (proximoEstado == -1){
            if (estadosFinais.count(estado)){
                break;
            }
            else{
                desfazerLeitura();
                cout << "ERRO LEXICO-> (Linha: " << linha << " Coluna: " << coluna << ") " << mensagensErro[estado] << "\n\t\t" << buffer << "\n\t\t^" << endl;
                readNextCaracter();
                error = true;
                break;
            }
        }
        else{
            if (proximoEstado != 0)
                buffer.push_back(caracter);
            estado = proximoEstado;
        }
    }while(caracter != EOF);

    Token token;

    if (!error){
        if (estadosFinais[estado] == "Id"){
            token = pesquisarTabelaSimbolos(buffer);
            if (token == Token()){
                token = Token(estadosFinais[estado], buffer, tiposDosEstados[estado]);
                inserirTabelaSimbolos(token);
            }
        }
        else if (estadosFinais[estado] == "Comentario"){
            desfazerLeitura();
            estado = 0;
            buffer.clear();
            return SCANNER();
        }
        else{
            token = Token(estadosFinais[estado], buffer, tiposDosEstados[estado]);
        }
        desfazerLeitura();
    }
    else{
        token = Token("ERRO", "NULO", "NULO");
    }

    estado = 0;
    buffer.clear();

    return token;
}

void Lexico::carregarAutomato()
{
    vector<char> alfabeto = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        ',', ';', ':', '.', '!', '?', '\\', '*', '+', '-', '/', '(', ')', '{', '}', '[', ']', '<', '>', '=', '\'', '"', '_', ' ', '\t', '\n', EOF
    };
    for (int i = 1; i <= alfabeto.size(); i++)
        idxOfCaracter[alfabeto[i-1]] = i;
    
    ifstream file(pathFileAutomato);
    assert(file.is_open());
    int numEstados, numTransicoes, estadoFinal;
    string descricao;
    file >> numEstados >> numTransicoes;
    transicoesAutomato.resize(numEstados, vector<int>(numTransicoes));
    for (int i = 0; i < numEstados; i++){
        for (int j = 0; j < numTransicoes; j++){
            file >> transicoesAutomato[i][j];
        }
    }
    for (int i = 0; i < numEstados; i++){
        file >> estadoFinal;
        file.ignore();
        getline(file, descricao);
        
        if (estadoFinal){
            estadosFinais[i] = descricao;
            getline(file, descricao);
            tiposDosEstados[i] = descricao;
        }
        else
            mensagensErro[i] = descricao;
    }
    file.close();
}

void Lexico::imprimirTabelaSimbolos()
{
    cout << "TABELA DE SIMBOLOS\n";
    for (Token token : tabelaDeSimbolos){
        cout << token << "\n";
    }
}
