#pragma once

#include <set>

class Token
{
public:
    static constexpr char print = ';';
    static constexpr char quit = 'q';

    static constexpr char number = '8';

    static const std::set<char> validTokens;

    char kind;
    double value;

    Token(char kind, double value = 0) : kind{kind}, value{value}
    {
    }
};
