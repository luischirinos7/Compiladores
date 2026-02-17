#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ArrayList.h" // TU ARRAYLIST
#include "Lexer.h" 

using namespace std;

int main() {
    // 1. Abrimos el archivo externo (Asegurate de crear este archivo en tu carpeta)
    ifstream archivo("helloworld.pas");
    
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo helloworld.pas" << endl;
        return 1;
    }

    // 2. Leemos todo el archivo y lo metemos en un string
    stringstream buffer;
    buffer << archivo.rdbuf();
    string codigoPascal = buffer.str();
    archivo.close();

    // 3. Pasamos el codigo al Lexer
    Lexer lexer(codigoPascal);
    Arraylist<Token> listaDeTokens; 
    
    // 4. Llenamos TU ArrayList
    Token currentToken = lexer.getNextToken();
    while (currentToken.type != TOKEN_EOF) {
        listaDeTokens.add(currentToken); 
        currentToken = lexer.getNextToken();
    }

    // 5. Imprimimos el resultado EXACTAMENTE como en tu foto
    for (int i = 0; i < listaDeTokens.size(); i++) {
        Token t = listaDeTokens.get(i);
        
        // Formato: Token: 'valor' (Tipo) at [linea,columna]
        cout << "Token: '" << t.value << "' (" << getTypeName(t.type) << ") at [" 
             << t.line << "," << t.col << "]" << endl;
    }

    return 0;
}