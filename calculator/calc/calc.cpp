#include "stdafx.h"
#include "Calculator.h"

int main()
{
	std::string expr = " sin(( 90) ) + 1 + cos(45) - sqrt(4)  ";
	std::string_view ref(expr);
	std::cout << std::endl << "result: " << Calculator::parseExpr(ref) << std::endl;
	return 0;
}

