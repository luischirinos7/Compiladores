#include "expression_parser.h"
#include <iostream>
#include <string>
#include <map>

int main() {
    ExpressionEvaluator calc;
    std::string entrada;
    std::map<std::string, double> variables;
    
    std::cout << "=== Analizador de expresiones ===" << std::endl;
    std::cout << "Escribe una expresion (o salir para terminar):" << std::endl;
    std::cout << "Ejemplos: 2+2 (5*3)/2 ,sin(pi/2), var x=5" << std::endl;
    std::cout << std::endl;
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, entrada);
        
        if (entrada == "salir") break;
        
        // Para definir variables
        if (entrada.substr(0, 4) == "var ") {
            size_t igual = entrada.find('=');
            if (igual != std::string::npos) {
                std::string nombre = entrada.substr(4, igual-4);
                double valor = std::stod(entrada.substr(igual+1));
                variables[nombre] = valor;
                std::cout << "Variable " << nombre << " = " << valor << std::endl;
            }
            continue;
        }
        
        try {
            double resultado = calc.eval(entrada, variables);
            std::cout << "= " << resultado << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    
    return 0;
}