#pragma once

#include <iosfwd>
#include <vector>

#include "Token.h"

namespace cas2 {

class TokenStream
{
public:
    TokenStream(std::istream& in) : in{in}
    {
    }

    Token getToken();
    void putback(const Token& t);

    // Ignore all input up to and including a print token or a newline.
    void flush();

private:
    std::istream& in;
    std::vector<Token> buffer;
};
}
