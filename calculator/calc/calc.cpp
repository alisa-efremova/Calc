#include "stdafx.h"
#include "Calculator.h"

int main()
{
	std::string expr = " 4+ 5*6 - 1/2  ";
	std::string_view ref(expr);
	std::cout << std::endl << "   " << Calculator::parseExpr(ref) << std::endl;
	return 0;
}

