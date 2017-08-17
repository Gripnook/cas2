#pragma once

#include <map>

#include "TokenStream.h"

namespace cas2 {

class Parser
{
public:
    Parser(TokenStream& ts) : ts{ts}
    {
    }

    double statement();

private:
    TokenStream& ts;
    std::map<std::string, double> symbolTable;

    double declaration();
    double expression();
    double subexpression();
    double term();
    double factor();
    double primary();
};
}
