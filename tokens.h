//
// Created by TNtube on 02/07/2021.
//

#ifndef MATHINTERPRETER_TOKENS_H
#define MATHINTERPRETER_TOKENS_H
#include <string>


enum TokenID {
    NUM,
    PLUS,
    MINUS,
    MULT,
    DIV,
    LPAR,
    RPAR
};

struct Token{
    TokenID type;
    std::string value;
};


#endif //MATHINTERPRETER_TOKENS_H
