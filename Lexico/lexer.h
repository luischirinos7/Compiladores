#ifndef LEXER_H
#define LEXER_H

#include <string>

using namespace std;

// 1. Tipos de Tokens
enum TokenType {
    TOKEN_ID,
    TOKEN_NUMERO,
    TOKEN_ASIGNACION,
    TOKEN_SUMA,
    TOKEN_RESTA,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_PAREN_IZQ,
    TOKEN_PAREN_DER,
    TOKEN_PUNTO_COMA,
    TOKEN_EOF,
    TOKEN_ERROR
};

// 2. Estructura del Token
struct Token {
    TokenType type;
    string value;

    Token() {
        type = TOKEN_ERROR;
        value = "";
    }

    Token(TokenType t, string v) {
        type = t;
        value = v;
    }
};

// Funcion para imprimir bonito (Declaracion)
string getTypeName(TokenType type);

// 3. Declaracion de la clase Lexer
class Lexer {
private:
    string text;
    int pos;
    char currentChar;

    void advance();
    void skipWhitespace();
    Token number();
    Token id();

public:
    Lexer(string text);
    Token getNextToken();
};

#endif // LEXER_H