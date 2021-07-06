//
// Created by TNtube on 02/07/2021.
//

#include "lexer.h"
#include <stdexcept>


namespace {
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
}


void Lexer::next(std::string::iterator & actual) {
    ++actual;
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
            tokens.push_back(Token{TokenKind::T_ADD, "+"});
            next(actual);
        }
        else if (*actual == '-') {
            tokens.push_back(Token{TokenKind::T_SUB, "-"});
            next(actual);
        }
        else if (*actual == '*') {
            tokens.push_back(Token{TokenKind::T_MUL, "*"});
            next(actual);
        }
        else if (*actual == '/') {
            tokens.push_back(Token{TokenKind::T_DIV, "/"});
            next(actual);
        }
        else if (*actual == '^') {
            tokens.push_back(Token{TokenKind::T_POW, "^"});
            next(actual);
        }
        else if (*actual == '(') {
            tokens.push_back(Token{TokenKind::T_LPAR, "("});
            next(actual);
        }
        else if (*actual == ')') {
            tokens.push_back(Token{TokenKind::T_RPAR, ")"});
            next(actual);
        }
        else if (*actual == '!') {
            tokens.push_back(Token{TokenKind::T_FACT, "!"});
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
    int countPoint {};

    auto start = actual;
    while(actual != text.end() && (*actual == '.' || isDigit(*actual))) {
        if(*actual == '.'){
            countPoint++;
            if (countPoint > 1){
                break;
            }
        }
        next(actual);
    }

    std::string num {start, actual};

    if (num.front() == '.') {
        num.insert(0, 1, '0');
    }
    if (num.back() == '.') {
        num.push_back('0');
    }

    return Token{TokenKind::T_NUM, num};
}

