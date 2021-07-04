//
// Created by TNtube on 03/07/2021.
//

#include "parser.h"
#include <stdexcept>
#include "tokens.h"

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
    Node result {term(actual)};

    while (actual != tokenVec.end() && (actual->type == TokenID::T_ADD || actual->type == TokenID::T_SUB)){
        switch (actual->type) {
            case TokenID::T_ADD:
                next(actual);
                return OpNode(result, term(actual), NodeOpKind::N_ADD);
            case TokenID::T_SUB:
                next(actual);
                return OpNode(result, term(actual), NodeOpKind::N_SUB);
        }
    }
    return Node();
}

Node Parser::term(std::vector<Token>::iterator & actual) {
    return Node();
}

Node Parser::factor(std::vector<Token>::iterator & actual) {
    return Node();
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