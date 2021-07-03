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
    tokens = {};
}


void Lexer::next(std::string::iterator & actual) {
    actual++;
}


std::vector<Token> Lexer::genTokens() {
    auto actual = text.begin();
    while(actual != text.end()) {

        if (isSpace(*actual)) {
            next(actual);
        }
        else if (*actual == '.' || isDigit(*actual)) {
            tokens.push_back(genNum(actual));
        }
        else if (*actual == '+') {
            tokens.push_back(Token{TokenID::PLUS});
            next(actual);
        }
        else if (*actual == '-') {
            tokens.push_back(Token{TokenID::MINUS});
            next(actual);
        }
        else if (*actual == '*') {
            tokens.push_back(Token{TokenID::MULT});
            next(actual);
        }
        else if (*actual == '/') {
            tokens.push_back(Token{TokenID::DIV});
            next(actual);
        }
        else if (*actual == '(') {
            tokens.push_back(Token{TokenID::LPAR});
            next(actual);
        }
        else if (*actual == ')') {
            tokens.push_back(Token{TokenID::RPAR});
            next(actual);
        }
        else {
            throw std::runtime_error(
                    std::string("Unknown char at ") +
                    std::to_string(std::distance(text.begin(), actual)));
        }

    }
    return tokens;
}

Token Lexer::genNum(std::string::iterator & actual) {
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
        next(actual);
    }

    if (num.front() == '.') {
        num.insert(0, 1, '0');
    }
    if (num.back() == '.') {
        num.push_back('0');
    }

    return Token{TokenID::NUM, num};
}

