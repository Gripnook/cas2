#include "Parser.h"

#include <cmath>
#include <stdexcept>

namespace cas2 {

double Parser::expression()
{
    double left = term();
    Token t = ts.getToken();
    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();
            break;
        case '-':
            left -= term();
            break;
        default:
            ts.putback(t);
            return left;
        }
        t = ts.getToken();
    }
}

double Parser::term()
{
    double left = primary();
    Token t = ts.getToken();
    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0)
                throw std::runtime_error("Division by zero");
            left /= d;
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0)
                throw std::runtime_error("Division by zero");
            left = fmod(left, d);
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
        t = ts.getToken();
    }
}

double Parser::primary()
{
    Token t = ts.getToken();
    switch (t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.getToken();
        if (t.kind != ')')
            throw std::runtime_error("Expected ')'");
        return d;
    }
    case Token::number:
        return t.value;
    case '+':
        return primary();
    case '-':
        return -primary();
    default:
        throw std::runtime_error("Expected primary");
    }
}
}
