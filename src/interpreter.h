//
// Created by TNtube on 05/07/2021.
//

#ifndef MATHINTERPRETER_INTERPRETER_H
#define MATHINTERPRETER_INTERPRETER_H

#include "nodes.h"
#include <memory>


namespace Interpreter{
    double eval(std::unique_ptr<Node> & node);
}


#endif //MATHINTERPRETER_INTERPRETER_H
