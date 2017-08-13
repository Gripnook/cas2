#include "Token.h"

const std::set<char> Token::validTokens = {
    Token::print, Token::quit, Token::number, '(', ')', '+', '-', '*', '/', '%'};
