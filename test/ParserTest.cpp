#include "catch.hpp"

#include "Parser.h"

#include <sstream>
#include <string>

using namespace cas2;

#define TEST_EQUALITY(expression)                    \
    TEST_CASE(expression)                            \
    {                                                \
        REQUIRE(lhs(expression) == rhs(expression)); \
    }

double evaluate(const std::string& statement)
{
    std::stringstream in(statement);

    TokenStream ts(in);
    Parser p(ts);

    return p.statement();
}

double lhs(const std::string& expression)
{
    auto index = expression.find("==");
    auto lhsExpression = expression.substr(0, index);

    return evaluate(lhsExpression);
}

double rhs(const std::string& expression)
{
    auto index = expression.find("==");
    auto rhsExpression =
        expression.substr(index + 2, expression.size() - index - 2);

    std::stringstream ss(rhsExpression);

    double result;
    ss >> result;
    return result;
}

TEST_EQUALITY("1 + 1 == 2")
TEST_EQUALITY("1 + 1.5 == 2.5")
TEST_EQUALITY("1 + 4 + 2 + 1 == 8")
TEST_EQUALITY("1+2+3+4+5+6+7+8 == 36")
TEST_EQUALITY("23 - 17 + 3 - 2 == 7")
TEST_EQUALITY("1 - 2 - 3 - 4 == -8")
TEST_EQUALITY("-1 + 1 == 0")
TEST_EQUALITY("-12 - 12 == -24")
TEST_EQUALITY("9 + 2 * 3 == 15")
TEST_EQUALITY("3 * 8 + 1 == 25")
TEST_EQUALITY("12 * 4 / 6 == 8")
TEST_EQUALITY("33 / 5 == 6.6")
TEST_EQUALITY("1 + 7 / 5 == 2.4")
TEST_EQUALITY("6 / 3 + 1 == 3")
TEST_EQUALITY("12 % 4 == 0")
TEST_EQUALITY("13 % 3 == 1")
TEST_EQUALITY("12.25 % 2 == 0.25")
TEST_EQUALITY("3 + 4 % 2 == 3")
TEST_EQUALITY("4 % 5 + 1 == 5")
TEST_EQUALITY("1*2/8%4+5-6 == -0.75")
TEST_EQUALITY("1234567890 == 1234567890")
TEST_EQUALITY("+1 == 1")
TEST_EQUALITY("1++2 == 3")
TEST_EQUALITY("++1 == 1")
TEST_EQUALITY("+-+-100 == 100")
TEST_EQUALITY("-2 == -2")
TEST_EQUALITY("+(100) - -10 == 110")
TEST_EQUALITY("let x = 100 == 100")
TEST_EQUALITY("let xy_10 = 100 == 100")

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
    CHECK_THROWS(evaluate("let 7 = 10"));
    CHECK_THROWS(evaluate("let x 10"));
    CHECK_THROWS(evaluate("let x"));
}

TEST_CASE("Declaration introduces a new symbol")
{
    std::stringstream in;
    in << "let x = 8 + 2" << std::endl << "x + 10";
    TokenStream ts(in);
    Parser p(ts);

    CHECK(p.statement() == 10);
    CHECK(p.statement() == 20);
}

TEST_CASE("Undeclared variable throws exception")
{
    std::stringstream in;
    in << "x + 10";
    TokenStream ts(in);
    Parser p(ts);

    REQUIRE_THROWS(p.statement());
}

TEST_CASE("Redeclaration of variable throws exception")
{
    std::stringstream in;
    in << "let x = 10" << std::endl << "let x = 20";
    TokenStream ts(in);
    Parser p(ts);

    p.statement();
    REQUIRE_THROWS(p.statement());
}

TEST_CASE("Variable names must start with a letter")
{
    std::stringstream in;
    in << "let 7up = 10";
    TokenStream ts(in);
    Parser p(ts);

    REQUIRE_THROWS(p.statement());
}

TEST_CASE("Variables can be reassigned")
{
    std::stringstream in;
    in << "let x = 10" << std::endl << "x = 20" << std::endl << "x + 10";
    TokenStream ts(in);
    Parser p(ts);

    CHECK(p.statement() == 10);
    CHECK(p.statement() == 20);
    CHECK(p.statement() == 30);
}

TEST_CASE("Variable assignments can be chained")
{
    std::stringstream in;
    in << "let x = 10" << std::endl
       << "let y = 20" << std::endl
       << "let z = 0" << std::endl
       << "x = y = z = 100" << std::endl
       << "x" << std::endl
       << "y" << std::endl
       << "z" << std::endl;
    TokenStream ts(in);
    Parser p(ts);

    CHECK(p.statement() == 10);
    CHECK(p.statement() == 20);
    CHECK(p.statement() == 0);
    CHECK(p.statement() == 100);
    CHECK(p.statement() == 100);
    CHECK(p.statement() == 100);
    CHECK(p.statement() == 100);
}

TEST_CASE("Assignment to an expression throws exception")
{
    std::stringstream in;
    in << "let x = 10" << std::endl
       << "let y = 20" << std::endl
       << "(x + y) = 100";
    TokenStream ts(in);
    Parser p(ts);

    CHECK(p.statement() == 10);
    CHECK(p.statement() == 20);
    CHECK(p.statement() == 30);
    CHECK_THROWS(p.statement());
}
