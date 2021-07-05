//
// Created by TNtube on 03/07/2021.
//

#include "parser.h"
#include <stdexcept>

void Parser::parse(std::unique_ptr<Node> & result) {
    auto actual = tokenVec.begin();
    if (actual == tokenVec.end()) {
        error("No expression");
    }

    expr(actual, result);

    if(actual != tokenVec.end()){
        error("Syntax Error");
    }
}

void Parser::expr(std::vector<Token>::iterator & actual, std::unique_ptr<Node> & node) {
    std::unique_ptr<Node> n1{new Node};
    node->node1 = std::move(n1);
    term(actual, node->node1);

    std::unique_ptr<Node> n2{new Node};
    node->node2 = std::move(n2);



    while (actual != tokenVec.end() && (actual->type == T_ADD || actual->type == T_SUB)){
        auto token = actual;
        if (actual->type == T_ADD) {
            next(actual);
            term(actual, node->node2);
            node->type = N_ADD;
            node->value = token->value;

        } else {
            next(actual);
            term(actual, node->node2);
            node->type = N_SUB;
            node->value = token->value;
        }
    }
}

void Parser::term(std::vector<Token>::iterator & actual, std::unique_ptr<Node> & node) {
    std::unique_ptr<Node> n1{new Node};
    node->node1 = std::move(n1);
    factor(actual, node->node1);

    std::unique_ptr<Node> n2{new Node};
    node->node2 = std::move(n2);


    while (actual != tokenVec.end() && (actual->type == T_MUL || actual->type == T_DIV)){
        auto token = actual;
        if (actual->type == T_MUL) {
            next(actual);
            factor(actual, node->node2);
            node->type = N_MUL;
            node->value = token->value;

        } else {
            next(actual);
            factor(actual, node->node2);
            node->type = N_DIV;
            node->value = token->value;
        }
    }
}

void Parser::factor(std::vector<Token>::iterator & actual, std::unique_ptr<Node> & node) {
    auto token = actual;

    if (token->type == TokenID::T_LPAR){
        next(actual);
        expr(actual, node);
        if (actual->type != TokenID::T_RPAR){
            error("Missing Closing Parenthesis");
        }
        next(actual);
    }
    else if (token->type == TokenID::T_NUM) {
        next(actual);
        node->type = N_NUM;
        node->value = token->value;
    }
    else if (token->type == TokenID::T_ADD) {
        next(actual);
        std::unique_ptr<Node> n1{new Node};
        node->node1 = std::move(n1);
        factor(actual, node->node1);
        node->type = N_PLUS;
        node->value = token->value;
    }
    else if (token->type == TokenID::T_SUB) {
        next(actual);
        std::unique_ptr<Node> n1{new Node};
        node->node1 = std::move(n1);
        factor(actual, node->node1);
        node->type = N_MINUS;
        node->value = token->value;
    } else {
        error("Invalid Syntax !");
    }

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