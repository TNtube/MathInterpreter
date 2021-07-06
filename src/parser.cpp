//
// Created by TNtube on 03/07/2021.
//

#include "parser.h"

#include <utility>

std::unique_ptr<Node> Parser::parse() {
    auto actual = tokenVec.begin();

    if (actual == tokenVec.end()) {
        error("No expression");
    }

    std::unique_ptr<Node> result = expr(actual);

    if(actual != tokenVec.end()){
        error("Invalid expression");
    }

    return result;
}

std::unique_ptr<Node> Parser::expr(std::vector<Token>::iterator & actual) {
    std::unique_ptr<Node> result = term(actual);

    while (actual != tokenVec.end() && (actual->type == TokenKind::T_ADD || actual->type == TokenKind::T_SUB)){
        auto token = actual;

        if (actual->type == TokenKind::T_ADD) {
            next(actual);
            result = std::make_unique<Node>(std::move(result), term(actual), NodeKind::N_ADD, token->value);
        }
        else {
            next(actual);
            result = std::make_unique<Node>(std::move(result), term(actual), NodeKind::N_SUB, token->value);
        }
    }

    return result;
}

std::unique_ptr<Node> Parser::term(std::vector<Token>::iterator & actual) {
    std::unique_ptr<Node> result = pow(actual);


    while (actual != tokenVec.end() && (actual->type == TokenKind::T_MUL || actual->type == TokenKind::T_DIV)){
        auto token = actual;

        if (actual->type == TokenKind::T_MUL) {
            next(actual);
            result = std::make_unique<Node>(std::move(result), pow(actual), NodeKind::N_MUL, token->value);
        }
        else {
            next(actual);
            result = std::make_unique<Node>(std::move(result), pow(actual), NodeKind::N_DIV, token->value);
        }
    }

    return result;
}

std::unique_ptr<Node> Parser::pow(std::vector<Token>::iterator & actual) {
    std::unique_ptr<Node> result = factor(actual);

    while (actual != tokenVec.end() && actual->type == TokenKind::T_POW){
        auto token = actual;
        next(actual);
        result = std::make_unique<Node>(std::move(result), factor(actual), NodeKind::N_POW, token->value);
    }

    return result;
}


std::unique_ptr<Node> Parser::factor(std::vector<Token>::iterator & actual) {
    auto token = actual;

    switch (token->type){
        case TokenKind::T_LPAR:
            {
            next(actual);
            auto result = expr(actual);

            if (actual->type != TokenKind::T_RPAR){
                error("Missing Closing Parenthesis");
            }
            next(actual);


            if (actual->type == TokenKind::T_FACT) {
                result = std::make_unique<Node>(result,NodeKind:: N_FACT, "!");
                next(actual);
            }

            return result;
            }
        case TokenKind::T_NUM:
            next(actual);

            if (actual->type == TokenKind::T_FACT) {
                auto result = std::make_unique<Node>(NodeKind::N_NUM, token->value);
                next(actual);

                return std::make_unique<Node>(result, NodeKind::N_FACT, "!");
            }

            return std::make_unique<Node>(NodeKind::N_NUM, token->value);
        case TokenKind::T_ADD:
            next(actual);

            return std::make_unique<Node>(factor(actual), NodeKind::N_PLUS, "+");
        case TokenKind::T_SUB:
            next(actual);

            return std::make_unique<Node>(factor(actual), NodeKind::N_MINUS, "-");
        default:
            error("Invalid expression");

    }
}

void Parser::next(std::vector<Token>::iterator & actual) {
    ++actual;
}

void Parser::error(std::string const & message) {
    throw std::runtime_error(message);
}