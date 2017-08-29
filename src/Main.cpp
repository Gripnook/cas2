#include <iostream>

#include "Calculator.h"

using namespace cas2;

int main()
{
    try
    {
        calculate(std::cin, std::cout);
        return 0;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        return 2;
    }
}
