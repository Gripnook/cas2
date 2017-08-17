#pragma once

#include <set>
#include <string>

namespace cas2 {

class Token
{
public:
    static constexpr char print = ';';
    static constexpr char quit = 'q';

    static constexpr char let = 'l';
    static constexpr char variable = 'n';
    static constexpr char number = '8';

    static const std::string quitkey;
    static const std::string declkey;

    static const std::set<char> validTokens;

    char kind;
    double value;
    std::string name;

    Token(char kind) : kind{kind}
    {
    }

    Token(char kind, double value) : kind{kind}, value{value}
    {
    }

    Token(char kind, std::string name) : kind{kind}, name{name}
    {
    }
};
}
