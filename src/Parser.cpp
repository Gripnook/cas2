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
    double left = factor();
    Token t = ts.getToken();
    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= factor();
            break;
        case '/':
        {
            double d = factor();
            if (d == 0)
                throw std::runtime_error("Division by zero");
            left /= d;
            break;
        }
        case '%':
        {
            double d = factor();
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

double Parser::factor()
{
    Token t = ts.getToken();
    switch (t.kind)
    {
    case '+':
        return primary();
    case '-':
        return -primary();
    default:
        ts.putback(t);
        return primary();
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
    default:
        throw std::runtime_error("Expected primary");
    }
}
}
