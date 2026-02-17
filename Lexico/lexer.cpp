#include "Lexer.h"
#include <cctype>

using namespace std;

// Implementacion de getTypeName
string getTypeName(TokenType type) {
    switch(type) {
        case TOKEN_ID: return "ID";
        case TOKEN_NUMERO: return "NUMERO";
        case TOKEN_ASIGNACION: return "ASIGNACION (:=)";
        case TOKEN_SUMA: return "SUMA (+)";
        case TOKEN_RESTA: return "RESTA (-)";
        case TOKEN_MULT: return "MULTIPLICACION (*)";
        case TOKEN_DIV: return "DIVISION (/)";
        case TOKEN_PAREN_IZQ: return "PAREN_IZQ";
        case TOKEN_PAREN_DER: return "PAREN_DER";
        case TOKEN_PUNTO_COMA: return "PUNTO_Y_COMA";
        case TOKEN_EOF: return "FIN_DE_ARCHIVO";
        default: return "ERROR_LEXICO";
    }
}

// Constructor
Lexer::Lexer(string text) {
    this->text = text;
    this->pos = 0;
    this->currentChar = text.length() > 0 ? text[0] : '\0';
}

// Metodos privados
void Lexer::advance() {
    pos++;
    if (pos >= text.length()) {
        currentChar = '\0';
    } else {
        currentChar = text[pos];
    }
}

void Lexer::skipWhitespace() {
    while (currentChar != '\0' && isspace(currentChar)) {
        advance();
    }
}

Token Lexer::number() {
    string result = "";
    while (currentChar != '\0' && isdigit(currentChar)) {
        result += currentChar;
        advance();
    }
    return Token(TOKEN_NUMERO, result);
}

Token Lexer::id() {
    string result = "";
    while (currentChar != '\0' && isalnum(currentChar)) {
        result += currentChar;
        advance();
    }
    return Token(TOKEN_ID, result);
}

// Metodo publico principal
Token Lexer::getNextToken() {
    while (currentChar != '\0') {
        if (isspace(currentChar)) {
            skipWhitespace();
            continue;
        }

        if (isalpha(currentChar)) { return id(); }
        if (isdigit(currentChar)) { return number(); }

        // Lookahead para :=
        if (currentChar == ':' && pos + 1 < text.length() && text[pos + 1] == '=') {
            advance(); 
            advance(); 
            return Token(TOKEN_ASIGNACION, ":=");
        }

        if (currentChar == '+') { advance(); return Token(TOKEN_SUMA, "+"); }
        if (currentChar == '-') { advance(); return Token(TOKEN_RESTA, "-"); }
        if (currentChar == '*') { advance(); return Token(TOKEN_MULT, "*"); }
        if (currentChar == '/') { advance(); return Token(TOKEN_DIV, "/"); }
        if (currentChar == '(') { advance(); return Token(TOKEN_PAREN_IZQ, "("); }
        if (currentChar == ')') { advance(); return Token(TOKEN_PAREN_DER, ")"); }
        if (currentChar == ';') { advance(); return Token(TOKEN_PUNTO_COMA, ";"); }

        string errorChar(1, currentChar);
        advance();
        return Token(TOKEN_ERROR, errorChar);
    }
    return Token(TOKEN_EOF, "");
}