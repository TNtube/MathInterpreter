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
        Node expr(std::vector<Token>::iterator & actual);
        Node term(std::vector<Token>::iterator & actual);
        Node factor(std::vector<Token>::iterator & actual);
        static void error(std::string const & message);
        static void next(std::vector<Token>::iterator & actual);

    public:
        explicit Parser(std::vector<Token> & tokens);
        Node parse();
};


#endif //MATHINTERPRETER_PARSER_H
