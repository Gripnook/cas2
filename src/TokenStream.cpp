#include "TokenStream.h"

#include <iostream>
#include <sstream>
#include <cctype>

namespace cas2 {

Token TokenStream::getToken()
{
    if (!buffer.empty())
    {
        Token t = buffer.back();
        buffer.pop_back();
        return t;
    }

    char ch;
    in >> ch;
    if (in.eof())
        return Token(Token::quit);
    else if (!in)
        throw std::runtime_error("Bad input stream");

    // We need to check for digits first since Token::number is a valid token.
    if (ch == '.' || isdigit(ch))
    {
        in.putback(ch);
        double val;
        in >> val;
        return Token(Token::number, val);
    }
    else if (isalpha(ch))
    {
        std::string name;
        name += ch;
        while (in.get(ch))
        {
            if (!(isalnum(ch) || ch == '_'))
            {
                in.putback(ch);
                break;
            }
            name += ch;
        }

        if (name == Token::declkey)
            return Token(Token::let);
        else if (name == Token::quitkey)
            return Token(Token::quit);
        else
            return Token(Token::variable, name);
    }
    else if (Token::validTokens.count(ch) != 0)
    {
        return Token(ch);
    }
    else
    {
        std::ostringstream oss;
        oss << "Bad token: " << ch;
        throw std::runtime_error(oss.str());
    }
}

void TokenStream::putback(const Token& t)
{
    buffer.push_back(t);
}

void TokenStream::flush()
{
    while (!buffer.empty())
    {
        Token t = buffer.back();
        buffer.pop_back();
        if (t.kind == Token::print)
            return;
    }

    for (char ch; in.get(ch);)
    {
        if (ch == Token::print || ch == '\n')
            return;
    }
}
}
