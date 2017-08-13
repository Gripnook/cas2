#include "catch.hpp"

#include "GrammarParser.h"

#include <sstream>
#include <string>

#include "TokenStream.h"

#define TEST_EXPRESSION(expression)                  \
    TEST_CASE(expression)                            \
    {                                                \
        REQUIRE(lhs(expression) == rhs(expression)); \
    }

double evaluate(const std::string& expression)
{
    std::stringstream in(expression);

    TokenStream ts(in);
    GrammarParser p(ts);

    return p.expression();
}

double lhs(const std::string& expression)
{
    auto index = expression.find('=');
    auto lhsExpression = expression.substr(0, index);

    return evaluate(lhsExpression);
}

double rhs(const std::string& expression)
{
    auto index = expression.find('=');
    auto rhsExpression =
        expression.substr(index + 1, expression.size() - index - 1);

    std::stringstream ss(rhsExpression);

    double result;
    ss >> result;
    return result;
}

TEST_EXPRESSION("1 + 1 = 2")
TEST_EXPRESSION("1 + 1.5 = 2.5")
TEST_EXPRESSION("1 + 4 + 2 + 1 = 8")
TEST_EXPRESSION("1+2+3+4+5+6+7+8 = 36")
TEST_EXPRESSION("23 - 17 + 3 - 2 = 7")
TEST_EXPRESSION("1 - 2 - 3 - 4 = -8")
TEST_EXPRESSION("-1 + 1 = 0")
TEST_EXPRESSION("-12 - 12 = -24")
TEST_EXPRESSION("9 + 2 * 3 = 15")
TEST_EXPRESSION("3 * 8 + 1 = 25")
TEST_EXPRESSION("12 * 4 / 6 = 8")
TEST_EXPRESSION("33 / 5 = 6.6")
TEST_EXPRESSION("1 + 7 / 5 = 2.4")
TEST_EXPRESSION("6 / 3 + 1 = 3")
TEST_EXPRESSION("12 % 4 = 0")
TEST_EXPRESSION("13 % 3 = 1")
TEST_EXPRESSION("12.25 % 2 = 0.25")
TEST_EXPRESSION("3 + 4 % 2 = 3")
TEST_EXPRESSION("4 % 5 + 1 = 5")
TEST_EXPRESSION("1*2/8%4+5-6 = -0.75")
TEST_EXPRESSION("1234567890 = 1234567890")
TEST_EXPRESSION("+1 = 1")
TEST_EXPRESSION("1++2 = 3")
TEST_EXPRESSION("-2 = -2")

TEST_CASE("Division by zero throws exception")
{
    REQUIRE_THROWS(evaluate("1 / 0"));
}

TEST_CASE("Taking modulus zero throws exception")
{
    REQUIRE_THROWS(evaluate("1 % 0"));
}

TEST_CASE("Invalid tokens throw exceptions")
{
    CHECK_THROWS(evaluate("!+2"));
    CHECK_THROWS(evaluate("'a'"));
}

TEST_CASE("Invalid inputs throw exceptions")
{
    CHECK_THROWS(evaluate("(1+3"));
    CHECK_THROWS(evaluate("(1+)"));
    CHECK_THROWS(evaluate("()"));
    CHECK_THROWS(evaluate("1+"));
    CHECK_THROWS(evaluate("1++"));
}
