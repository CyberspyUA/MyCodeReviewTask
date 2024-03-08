/**
 * IDE: Visual Studio 2022
 * C++ Standard: ISO C++14
 * Compiler: Microsoft Visual C++ (MSVC)
 */
#include "MyVectorRefactored.hpp"

int main()
{
    MyVectorRefactored<int> firstTestVector;
    firstTestVector.push_back(1, "fizz");
    firstTestVector.push_back(2, "buzz");
    firstTestVector.push_back(3, "fizzbuzz");
    MyVectorRefactored<int> secondTestVector (firstTestVector);
    MyVectorRefactored<int> thirdTestVector;
    thirdTestVector = firstTestVector;
    secondTestVector.push_back(4, "buzzfizz");
    secondTestVector["buzzfizz"];
    try
    {
	    firstTestVector["buzzfizz"];
    }
    catch (const std::exception& exceptionName)
    {
	    std::cerr << exceptionName.what();
    }
    return 0;
}