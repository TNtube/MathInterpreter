//
// Created by TNtube on 03/07/2021.
//

#ifndef MATHINTERPRETER_PARSER_H
#define MATHINTERPRETER_PARSER_H

#include "nodes.h"
#include "tokens.h"
#include <vector>


class Parser {
    private:
        std::vector<Token> tokenVec;
        void expr(std::vector<Token>::iterator & actual, std::unique_ptr<Node> & node);
        void term(std::vector<Token>::iterator & actual, std::unique_ptr<Node> & node);
        void factor(std::vector<Token>::iterator & actual, std::unique_ptr<Node> & node);
        static void error(std::string const & message);
        static void next(std::vector<Token>::iterator & actual);

    public:
        explicit Parser(std::vector<Token> & tokens);
        void parse(std::unique_ptr<Node> & result);
};


#endif //MATHINTERPRETER_PARSER_H
