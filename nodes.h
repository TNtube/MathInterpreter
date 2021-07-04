//
// Created by TNtube on 03/07/2021.
//

#ifndef MATHINTERPRETER_NODES_H
#define MATHINTERPRETER_NODES_H

#include <string>


enum NodeKind {
    N_NUM,
    N_ADD,
    N_SUB,
    N_MUL,
    N_DIV,
    N_PLUS,
    N_MINUS,
    N_POWER
};

struct Node{
    Node* node1 = nullptr;
    Node* node2 = nullptr;
    NodeKind type;
    std::string value;
};

#endif //MATHINTERPRETER_NODES_H
