#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"

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
        }
        catch (std::runtime_error & error){
            std::cout << error.what() << std::endl;
            continue;
        }

        Parser parser(tokenizedEntry);
        Node nodes = parser.parse();

        std::cout << &nodes.node1 << std::endl;


    }
    return 0;
}
