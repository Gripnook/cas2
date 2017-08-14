#include "Token.h"

namespace cas2 {

const std::set<char> Token::validTokens = {
    Token::print, Token::quit, Token::number, '(', ')', '+', '-', '*', '/', '%'};
}
