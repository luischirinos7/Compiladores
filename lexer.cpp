#include "Lexer.h"
#include <cctype>
#include <algorithm> 

using namespace std;

string getTypeName(TokenType type) {
    switch(type) {
        case TOKEN_KEYWORD: return "Keyword";
        case TOKEN_IDENTIFIER: return "Identifier";
        case TOKEN_DELIMITER: return "Delimiter";
        case TOKEN_OPERATOR: return "Operator";
        case TOKEN_STRING: return "String";
        case TOKEN_FUNCTION: return "Function";
        case TOKEN_NUMERO: return "Numero";
        case TOKEN_EOF: return "EOF";
        default: return "Error";
    }
}

Lexer::Lexer(string text) {
    this->text = text;
    this->pos = 0;
    this->line = 1; 
    this->col = 1;  
    this->currentChar = text.length() > 0 ? text[0] : '\0';
}

void Lexer::advance() {
    if (currentChar == '\n') {
        line++;
        col = 1; 
    } else {
        col++; 
    }
    
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

Token Lexer::stringLiteral() {
    int startLine = line;
    int startCol = col;
    string result = "";
    
    advance(); 
    
    while (currentChar != '\0' && currentChar != '\'') {
        result += currentChar;
        advance();
    }
    
    advance(); 
    return Token(TOKEN_STRING, result, startLine, startCol);
}

Token Lexer::number() {
    int startLine = line;
    int startCol = col;
    string result = "";
    while (currentChar != '\0' && isdigit(currentChar)) {
        result += currentChar;
        advance();
    }
    return Token(TOKEN_NUMERO, result, startLine, startCol);
}

Token Lexer::id() {
    int startLine = line;
    int startCol = col;
    string result = "";
    
    while (currentChar != '\0' && (isalnum(currentChar) || currentChar == '_')) {
        result += currentChar;
        advance();
    }
    
    string lowerStr = result;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    
    if (lowerStr == "program" || lowerStr == "var" || lowerStr == "string" || 
        lowerStr == "begin" || lowerStr == "end") {
        return Token(TOKEN_KEYWORD, result, startLine, startCol);
    }
    
    if (lowerStr == "writeln" || lowerStr == "readln" || lowerStr == "write") {
        return Token(TOKEN_FUNCTION, result, startLine, startCol);
    }
    
    return Token(TOKEN_IDENTIFIER, result, startLine, startCol);
}

Token Lexer::getNextToken() {
    while (currentChar != '\0') {
        
        if (isspace(currentChar)) {
            skipWhitespace();
            continue;
        }

        if (isalpha(currentChar)) { return id(); }
        if (isdigit(currentChar)) { return number(); }
        
        if (currentChar == '\'') { return stringLiteral(); }

        if (currentChar == ':' && pos + 1 < text.length() && text[pos + 1] == '=') {
            int startLine = line;
            int startCol = col;
            advance(); advance(); 
            return Token(TOKEN_OPERATOR, ":=", startLine, startCol);
        }

        int startLine = line;
        int startCol = col;
        char c = currentChar;
        advance();
        
        if (c == ';' || c == ':' || c == ',' || c == '.') {
            return Token(TOKEN_DELIMITER, string(1, c), startLine, startCol);
        }
        
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
            return Token(TOKEN_OPERATOR, string(1, c), startLine, startCol);
        }
        
        if (c == '(' || c == ')') {
            return Token(TOKEN_DELIMITER, string(1, c), startLine, startCol);
        }

        return Token(TOKEN_ERROR, string(1, c), startLine, startCol);
    }
    return Token(TOKEN_EOF, "", line, col);
}