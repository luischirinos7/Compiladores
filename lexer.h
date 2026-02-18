#ifndef LEXER_H
#define LEXER_H

#include <string>

using namespace std;

enum TokenType {
    TOKEN_KEYWORD,    
    TOKEN_IDENTIFIER, 
    TOKEN_DELIMITER,  
    TOKEN_OPERATOR,   
    TOKEN_STRING,     
    TOKEN_FUNCTION,   
    TOKEN_NUMERO,     
    TOKEN_EOF,
    TOKEN_ERROR
};

struct Token {
    TokenType type;
    string value;
    int line;
    int col;

    Token() {
        type = TOKEN_ERROR;
        value = "";
        line = 0;
        col = 0;
    }

    Token(TokenType t, string v, int l, int c) {
        type = t;
        value = v;
        line = l;
        col = c;
    }
};

string getTypeName(TokenType type);

class Lexer {
private:
    string text;
    int pos;
    char currentChar;
    int line; 
    int col;  

    void advance();
    void skipWhitespace();
    Token number();
    Token id();
    Token stringLiteral(); 

public:
    Lexer(string text);
    Token getNextToken();
};

#endif 