//
// Created by TNtube on 03/07/2021.
//

#include "parser.h"
#include <stdexcept>

Node Parser::parse() {
    auto actual = tokenVec.begin();
    if (actual == tokenVec.end()) {
        error("No expression");
    }

    Node result {expr(actual)};

    if(actual != tokenVec.end()){
        error("Syntax Error");
    }
    return result;
}

Node Parser::expr(std::vector<Token>::iterator & actual) {
    Node result = term(actual);
    Node ter;

    while (actual != tokenVec.end() && (actual->type == TokenID::T_ADD || actual->type == TokenID::T_SUB)){
        switch (actual->type) {
            case TokenID::T_ADD:
                next(actual);
                ter = term(actual);
                return Node{&result, &ter, NodeKind::N_ADD};
            case TokenID::T_SUB:
                next(actual);
                ter = term(actual);
                return Node{&result, &ter, NodeKind::N_SUB};

            default:
                continue;
        }
    }
}

Node Parser::term(std::vector<Token>::iterator & actual) {
    Node result = factor(actual);
    Node fact;

    while (actual != tokenVec.end() && (actual->type == TokenID::T_MUL || actual->type == TokenID::T_DIV)){
        switch (actual->type) {
            case TokenID::T_NUM:
                next(actual);
                fact = factor(actual);
                return Node{&result, &fact, NodeKind::N_MUL};
            case TokenID::T_SUB:
                next(actual);
                fact = factor(actual);
                return Node{&result, &fact, NodeKind::N_DIV};

            default:
                continue;
        }
    }
}

Node Parser::factor(std::vector<Token>::iterator & actual) {
    auto token = actual;

    Node fact;

    if (token->type == TokenID::T_LPAR){
        next(actual);
        Node result = expr(actual);
        if (actual->type != TokenID::T_RPAR){
            error("Invalid Syntax !");
        }
        next(actual);
        return result;
    }
    else if (token->type == TokenID::T_NUM) {
        next(actual);
        return Node{nullptr, nullptr, NodeKind::N_NUM, token->value};
    }
    else if (token->type == TokenID::T_ADD) {
        next(actual);
        fact = factor(actual);
        return Node{&fact, nullptr, NodeKind::N_PLUS};
    }
    else if (token->type == TokenID::T_SUB) {
        next(actual);
        fact = factor(actual);
        return Node{&fact, nullptr, NodeKind::N_MINUS};
    }

    error("Invalid Syntax !");
}

void Parser::next(std::vector<Token>::iterator & actual) {
    actual++;
}

void Parser::error(std::string const & message) {
    throw std::runtime_error(message);
}

Parser::Parser(std::vector<Token> & tokens)
 : tokenVec(tokens)
{}