#include <iostream>
#include <string>
#include "ArrayList.h"
#include "Lexer.h" 

using namespace std;

int main() {
    string codigoPascal = "resultado := 45 + variable * (10 - 2);";
    cout << "== INICIANDO COMPILADOR ==" << endl;
    cout << "Codigo fuente: " << codigoPascal << "\n" << endl;
    
    Lexer lexer(codigoPascal);
    Arraylist<Token> listaDeTokens; 
    
    Token currentToken = lexer.getNextToken();
    while (currentToken.type != TOKEN_EOF) {
        listaDeTokens.add(currentToken); 
        currentToken = lexer.getNextToken();
    }
    listaDeTokens.add(currentToken); 

    cout << "== TOKENS EXTRAIDOS Y GUARDADOS EN ARRAYLIST ==" << endl;
    cout << "Total de tokens guardados: " << listaDeTokens.size() << "\n" << endl;

    for (int i = 0; i < listaDeTokens.size(); i++) {
        Token t = listaDeTokens.get(i);
        cout << "Token[" << i << "] -> Tipo: [" << getTypeName(t.type) << "] \t Valor: '" << t.value << "'" << endl;
    }

    return 0;
}