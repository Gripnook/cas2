#pragma once

#include "TokenStream.h"

class GrammarParser
{
public:
    GrammarParser(TokenStream& ts) : ts{ts}
    {
    }

    double expression();

private:
    TokenStream& ts;

    double term();
    double primary();
};
