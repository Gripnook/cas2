#include "Parser.h"

#include <cmath>
#include <stdexcept>

namespace cas2 {

double Parser::statement()
{
    Token t = ts.getToken();
    if (t.kind == Token::let)
    {
        return declaration();
    }
    else
    {
        ts.putback(t);
        return expression();
    }
}

double Parser::declaration()
{
    Token t1 = ts.getToken();
    if (t1.kind != Token::variable)
        throw std::runtime_error("Expected variable name in declaration");

    Token t2 = ts.getToken();
    if (t2.kind != '=')
        throw std::runtime_error("Expected '=' in declaration of " + t1.name);

    double d = expression();
    if (symbolTable.count(t1.name) != 0)
        throw std::runtime_error("Redeclaration of " + t1.name);
    symbolTable.emplace(t1.name, d);
    return d;
}

double Parser::expression()
{
    Token t = ts.getToken();
    if (t.kind == Token::variable)
    {
        if (symbolTable.count(t.name) == 0)
            throw std::runtime_error("Undeclared variable: " + t.name);
        Token t2 = ts.getToken();
        if (t2.kind == '=')
        {
            double d = expression();
            symbolTable.at(t.name) = d;
            return d;
        }
        else
        {
            ts.putback(t2);
        }
    }

    ts.putback(t);
    return subexpression();
}

double Parser::subexpression()
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
    case Token::variable:
        if (symbolTable.count(t.name) == 0)
            throw std::runtime_error("Undeclared variable: " + t.name);
        return symbolTable.at(t.name);
    default:
        throw std::runtime_error("Expected primary");
    }
}
}
