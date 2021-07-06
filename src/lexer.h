//
// Created by TNtube on 02/07/2021.
//

#ifndef MATHINTERPRETER_LEXER_H
#define MATHINTERPRETER_LEXER_H
#include <string>
#include "tokens.h"
#include <utility>
#include <vector>

class Lexer {
    private:
        std::string text;
        std::vector<Token> tokens;
        static void next(std::string::iterator & actual);
        Token genNum(std::string::iterator & actual);

    public:
        std::vector<Token> genTokens();
        explicit Lexer(std::string txt):
                text(std::move(txt)), tokens({})
        {}
};


#endif //MATHINTERPRETER_LEXER_H
