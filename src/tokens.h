//
// Created by TNtube on 02/07/2021.
//

#ifndef MATHINTERPRETER_TOKENS_H
#define MATHINTERPRETER_TOKENS_H
#include <string>


enum class TokenKind {
    T_NUM,
    T_ADD,
    T_SUB,
    T_MUL,
    T_DIV,
    T_POW,
    T_FACT,
    T_LPAR,
    T_RPAR
};

struct Token{
    TokenKind type;
    std::string value;
};


#endif //MATHINTERPRETER_TOKENS_H
