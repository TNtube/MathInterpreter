//
// Created by TNtube on 05/07/2021.
//

#include "interpreter.h"
#include <stdexcept>
#include <cmath>


namespace {
    double add(std::unique_ptr<Node> & node) {
        return Interpreter::eval(node->node1) + Interpreter::eval(node->node2);
    }

    double sub(std::unique_ptr<Node> & node) {
        return Interpreter::eval(node->node1) - Interpreter::eval(node->node2);
    }

    double mul(std::unique_ptr<Node> & node) {
        return Interpreter::eval(node->node1) * Interpreter::eval(node->node2);
    }

    double div(std::unique_ptr<Node> & node) {
        double x = Interpreter::eval(node->node1);
        double y = Interpreter::eval(node->node2);
        if (!bool(y)) {
            throw std::runtime_error("Math error, can't divide by 0");
        }
        return x / y;
    }

    double plus(std::unique_ptr<Node> & node) {
        return +Interpreter::eval(node->node1);
    }

    double minus(std::unique_ptr<Node> & node) {
        return -Interpreter::eval(node->node1);
    }

    double pow(std::unique_ptr<Node> &node) {
        return std::pow(Interpreter::eval(node->node1), Interpreter::eval(node->node2));
    }

    double fact(std::unique_ptr<Node> &node) {
        return std::tgamma(Interpreter::eval(node->node1) + 1);
    }
}

double Interpreter::eval(std::unique_ptr<Node> & node) {
    switch (node->type) {
        case NodeKind::N_NUM:
            return std::stod(node->value);
        case NodeKind::N_ADD:
            return add(node);
        case NodeKind::N_SUB:
            return sub(node);
        case NodeKind::N_MUL:
            return mul(node);
        case NodeKind::N_DIV:
            return div(node);
        case NodeKind::N_PLUS:
            return plus(node);
        case NodeKind::N_MINUS:
            return minus(node);
        case NodeKind::N_POW:
            return pow(node);
        case NodeKind::N_FACT:
            return fact(node);
        default:
            return 0;
    }
}

