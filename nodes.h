//
// Created by TNtube on 03/07/2021.
//

#ifndef MATHINTERPRETER_NODES_H
#define MATHINTERPRETER_NODES_H


enum NodeOpKind {
    N_ADD,
    N_SUB,
    N_MUL,
    N_DIV,
    N_PLUS,
    N_MINUS,
    N_POWER
};

struct Node {};


struct NumberNode : Node {
    int value;
};

struct OpNode : Node {
    Node node1;
    Node node2;
    NodeOpKind type;
    OpNode(Node n1, Node n2, NodeOpKind nType) : node1(n1), node2(n2), type(nType) {}
};

#endif //MATHINTERPRETER_NODES_H
