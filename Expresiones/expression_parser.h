#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <string>
#include <map>

class ExpressionParser {
private:
    std::string input;
    size_t pos;
    char currentChar;
    std::map<std::string, double> variables;
    
    void nextChar();
    bool eat(char expected);
    double parseExpression();
    double parseTerm();
    double parseFactor();
    
public:
    ExpressionParser();
    double evaluate(const std::string& expr);
    void setVariable(const std::string& name, double value);
    void clearVariables();
};

class ExpressionEvaluator {
private:
    ExpressionParser parser;
    
public:
    double eval(const std::string& expr);
    double eval(const std::string& expr, const std::map<std::string, double>& vars);
};

#endif
