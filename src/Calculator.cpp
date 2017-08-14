#include "Calculator.h"

#include <iostream>

#include "TokenStream.h"
#include "Parser.h"

namespace cas2 {

void calculate(std::istream& in, std::ostream& out)
{
    TokenStream ts(in);
    Parser p(ts);
    while (in)
    {
        try
        {
            out << "> ";

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
}
