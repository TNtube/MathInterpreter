#include <iostream>
#include <string>
#include "lexer.h"

int main() {
    std::string entry {};
    while(true){
        std::cout << ">";
        std::cin >> entry;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

        // Debugging

        for(auto & token : tokenizedEntry){
            std::cout << token.type << " : " << token.value << std::endl;
        }


    }
    return 0;
}
