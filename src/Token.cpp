#include "Token.h"

namespace cas2 {

const std::string Token::quitkey = "quit";
const std::string Token::declkey = "let";

const std::set<char> Token::validTokens = {Token::print,
                                           Token::quit,
                                           Token::let,
                                           Token::variable,
                                           Token::number,
                                           '(',
                                           ')',
                                           '+',
                                           '-',
                                           '*',
                                           '/',
                                           '%',
                                           '='};
}
