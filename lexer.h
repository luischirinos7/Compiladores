#ifndef LEXER_H
#define LEXER_H

#include <string>

using namespace std;

// 1. Tipos de Tokens exactos como pide tu consola
enum TokenType {
    TOKEN_KEYWORD,    // program, var, string, begin, end
    TOKEN_IDENTIFIER, // HelloWorld, message
    TOKEN_DELIMITER,  // ; : , .
    TOKEN_OPERATOR,   // := + - * /
    TOKEN_STRING,     // 'Hello, World!'
    TOKEN_FUNCTION,   // writeln
    TOKEN_NUMERO,     // 123
    TOKEN_EOF,
    TOKEN_ERROR
};

// 2. Estructura del Token (Ahora con linea y columna)
struct Token {
    TokenType type;
    string value;
    int line;
    int col;

    // Constructor por defecto (Para que no explote tu ArrayList)
    Token() {
        type = TOKEN_ERROR;
        value = "";
        line = 0;
        col = 0;
    }

    // Constructor completo
    Token(TokenType t, string v, int l, int c) {
        type = t;
        value = v;
        line = l;
        col = c;
    }
};

string getTypeName(TokenType type);

// 3. Declaracion de la clase Lexer
class Lexer {
private:
    string text;
    int pos;
    char currentChar;
    int line; // ¡NUEVO! Rastreador de linea
    int col;  // ¡NUEVO! Rastreador de columna

    void advance();
    void skipWhitespace();
    Token number();
    Token id();
    Token stringLiteral(); // ¡NUEVO! Para leer 'Hello, World!'

public:
    Lexer(string text);
    Token getNextToken();
};

#endif // LEXER_H