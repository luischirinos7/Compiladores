#include "expression_parser.h"
#include <cmath>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <iostream>

ExpressionParser::ExpressionParser() : pos(0), currentChar(' ') {}

void ExpressionParser::nextChar() {
    if (pos < input.length()) {
        currentChar = input[pos++];
    } else {
        currentChar = '\0';
    }
}

bool ExpressionParser::eat(char expected) {
    while (currentChar == ' ') nextChar();
    if (currentChar == expected) {
        nextChar();
        return true;
    }
    return false;
}

double ExpressionParser::parseExpression() {
    double value = parseTerm();
    while (true) {
        if (eat('+')) {
            value += parseTerm();
        } else if (eat('-')) {
            value -= parseTerm();
        } else {
            break;
        }
    }
    return value;
}

double ExpressionParser::parseTerm() {
    double value = parseFactor();
    while (true) {
        if (eat('*')) {
            value *= parseFactor();
        } else if (eat('/')) {
            value /= parseFactor();
        } else {
            break;
        }
    }
    return value;
}

double ExpressionParser::parseFactor() {
    if (eat('+')) return parseFactor();
    if (eat('-')) return -parseFactor();
    
    double value;
    
    if (eat('(')) {
        value = parseExpression();
        if (!eat(')')) {
            throw std::runtime_error("Error: Falta paréntesis de cierre");
        }
    } else if (isdigit(currentChar) || currentChar == '.') {
        std::string numStr;
        while (isdigit(currentChar) || currentChar == '.') {
            numStr += currentChar;
            nextChar();
        }
        value = std::stod(numStr);
    } else if (isalpha(currentChar)) {
        std::string ident;
        while (isalnum(currentChar) || currentChar == '_') {
            ident += currentChar;
            nextChar();
        }
        
        if (ident == "pi") {
            value = 3.14159265358979323846;
        } else if (ident == "e") {
            value = 2.71828182845904523536;
        } else if (ident == "sin" && eat('(')) {
            value = sin(parseExpression());
            if (!eat(')')) throw std::runtime_error("Error: Falta ) en sin()");
        } else if (ident == "cos" && eat('(')) {
            value = cos(parseExpression());
            if (!eat(')')) throw std::runtime_error("Error: Falta ) en cos()");
        } else if (ident == "tan" && eat('(')) {
            value = tan(parseExpression());
            if (!eat(')')) throw std::runtime_error("Error: Falta ) en tan()");
        } else if (ident == "sqrt" && eat('(')) {
            value = sqrt(parseExpression());
            if (!eat(')')) throw std::runtime_error("Error: Falta ) en sqrt()");
        } else if (ident == "log" && eat('(')) {
            value = log(parseExpression());
            if (!eat(')')) throw std::runtime_error("Error: Falta ) en log()");
        } else if (ident == "exp" && eat('(')) {
            value = exp(parseExpression());
            if (!eat(')')) throw std::runtime_error("Error: Falta ) en exp()");
        } else {
            auto it = variables.find(ident);
            if (it != variables.end()) {
                value = it->second;
            } else {
                throw std::runtime_error("Error: Variable no definida: " + ident);
            }
        }
    } else {
        throw std::runtime_error("Error: Carácter inesperado");
    }
    
    return value;
}

double ExpressionParser::evaluate(const std::string& expr) {
    input = expr;
    pos = 0;
    nextChar();
    
    double result = parseExpression();
    
    while (currentChar == ' ') nextChar();
    if (currentChar != '\0') {
        throw std::runtime_error("Error: Caracteres extra al final de la expresión");
    }
    
    return result;
}

void ExpressionParser::setVariable(const std::string& name, double value) {
    variables[name] = value;
}

void ExpressionParser::clearVariables() {
    variables.clear();
}

double ExpressionEvaluator::eval(const std::string& expr) {
    return parser.evaluate(expr);
}

double ExpressionEvaluator::eval(const std::string& expr, 
                                 const std::map<std::string, double>& vars) {
    parser.clearVariables();
    for (const auto& var : vars) {
        parser.setVariable(var.first, var.second);
    }
    return parser.evaluate(expr);
}