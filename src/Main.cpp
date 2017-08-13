#include <iostream>

#include "Calculator.h"

int main()
{
    try
    {
        calculate(std::cin, std::cout);
        return 0;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        return 2;
    }
}
