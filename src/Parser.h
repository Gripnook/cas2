#pragma once

#include "TokenStream.h"

namespace cas2 {

class Parser
{
public:
    Parser(TokenStream& ts) : ts{ts}
    {
    }

    double expression();

private:
    TokenStream& ts;

    double term();
    double factor();
    double primary();
};
}
