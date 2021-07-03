//
// Created by TNtube on 02/07/2021.
//

#ifndef MATHINTERPRETER_LEXER_H
#define MATHINTERPRETER_LEXER_H
#include <string>
#include "tokens.h"
#include <vector>

class Lexer {
    private:
        std::string text;
        std::string::iterator actual;
        std::vector<Token> tokens;
        void next();
        Token genNum();

    public:
        std::vector<Token> genTokens();
        explicit Lexer(std::string & text);
};


#endif //MATHINTERPRETER_LEXER_H
