//
// Created by TNtube on 03/07/2021.
//

#ifndef MATHINTERPRETER_NODES_H
#define MATHINTERPRETER_NODES_H

#include <string>
#include <memory>


enum NodeKind {
    N_NUM,
    N_ADD,
    N_SUB,
    N_MUL,
    N_DIV,
    N_PLUS,
    N_MINUS,
    N_POWER,
    N_DEFAULT
};

struct Node{
    std::unique_ptr<Node> node1;
    std::unique_ptr<Node> node2;
    NodeKind type;
    std::string value;
    Node() : node1(), node2(), type(N_DEFAULT), value(){}
};

#endif //MATHINTERPRETER_NODES_H
