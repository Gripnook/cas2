#include "Calculator.h"

#include <iostream>

#include "TokenStream.h"
#include "GrammarParser.h"

void calculate(std::istream& in, std::ostream& out)
{
    TokenStream ts(in);
    GrammarParser p(ts);
    while (in)
    {
        try
        {
            std::cout << "> ";
            Token t = ts.getToken();
            while (t.kind == Token::print)
                t = ts.getToken();

            if (t.kind == Token::quit)
                return;

            ts.putback(t);
            out << p.expression() << std::endl;
        }
        catch (std::exception& e)
        {
            out << e.what() << std::endl;
            ts.flush();
        }
    }
}
