#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"


void displayTree(std::unique_ptr<Node> & node) {
    std::cout << "(";
    if(node->node1 != nullptr) {
        displayTree(node->node1);
    }
    std::cout << " " << node->value << " ";
    if(node->node2 != nullptr) {
        displayTree(node->node2);
    }
    std::cout << ")";
}

int main() {
    std::string entry {};
    while(true){
        std::cout << ">";
        std::getline(std::cin, entry);
        if(entry == "quit"){
            break;
        }

        Lexer lexer(entry);
        std::vector<Token> tokenizedEntry;
        try{
            tokenizedEntry = lexer.genTokens();
            std::unique_ptr<Node> ast;
            Parser parser(tokenizedEntry);
            ast = parser.parse();
            std::cout << Interpreter::eval(ast) << "\n";
        }
        catch (std::runtime_error & error){
            std::cout << "Error : " << error.what() << std::endl;
            continue;
        }
    }
    return 0;
}
