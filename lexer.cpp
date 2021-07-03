//
// Created by TNtube on 02/07/2021.
//

#include "lexer.h"
#include <stdexcept>
#include <iostream>



bool isSpace(char character)
{
    switch (character)
    {
        case ' ':
        case '\f':
        case '\n':
        case '\r':
        case '\t':
        case '\v':
            return true;

        default:
            return false;
    }
}

bool isDigit(char character)
{
    return (character >= '0' && character <= '9');
}




Lexer::Lexer(std::string & txt){
    text = txt;
    actual = text.begin();
    tokens = {};
}


void Lexer::next() {
    actual++;
}


std::vector<Token> Lexer::genTokens() {
    while(actual != text.end()) {

        if (isSpace(*actual)) {
            next();
        }
        else if (*actual == '.' || isDigit(*actual)) {
            tokens.push_back(genNum());
        }
        else if (*actual == '+') {
            tokens.push_back(Token{TokenID::PLUS});
            next();
        }
        else if (*actual == '-') {
            tokens.push_back(Token{TokenID::MINUS});
            next();
        }
        else if (*actual == '*') {
            tokens.push_back(Token{TokenID::MULT});
            next();
        }
        else if (*actual == '/') {
            tokens.push_back(Token{TokenID::DIV});
            next();
        }
        else if (*actual == '(') {
            tokens.push_back(Token{TokenID::LPAR});
            next();
        }
        else if (*actual == ')') {
            tokens.push_back(Token{TokenID::RPAR});
            next();
        }
        else {
            throw std::runtime_error(
                    std::string("Unknown char at ") +
                    std::to_string(std::distance(text.begin(), actual)));
        }

    }
    return tokens;
}

Token Lexer::genNum() {
    std::string num {};
    int countPoint {};

    while(actual != text.end() && (*actual == '.' || isdigit(*actual))) {
        if(*actual == '.'){
            countPoint++;
            if (countPoint > 1){
                break;
            }
        }
        num.push_back(*actual);
        next();
    }

    if (num.front() == '.') {
        num.insert(0, 1, '0');
    }
    if (num.back() == '.') {
        num.push_back('0');
    }

    return Token{TokenID::NUM, num};
}

