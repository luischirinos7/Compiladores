#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ArrayList.h" 
#include "Lexer.h" 

using namespace std;

int main() {
    ifstream archivo("helloworld.pas");
    
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo helloworld.pas" << endl;
        return 1;
    }

    stringstream buffer;
    buffer << archivo.rdbuf();
    string codigoPascal = buffer.str();
    archivo.close();

    Lexer lexer(codigoPascal);
    Arraylist<Token> listaDeTokens; 
    
    Token currentToken = lexer.getNextToken();
    while (currentToken.type != TOKEN_EOF) {
        listaDeTokens.add(currentToken); 
        currentToken = lexer.getNextToken();
    }

    for (int i = 0; i < listaDeTokens.size(); i++) {
        Token t = listaDeTokens.get(i);
        
        cout << "Token: '" << t.value << "' (" << getTypeName(t.type) << ") at [" 
             << t.line << "," << t.col << "]" << endl;
    }

    return 0;
}