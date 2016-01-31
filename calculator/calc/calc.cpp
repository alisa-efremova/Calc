#include "stdafx.h"
#include "Calculator.h"

int main()
{
	std::string expr = "  152.3   +  42 +  0.512  ";
	boost::string_ref ref(expr);
	std::cout << Calculator::parseExpr(ref) << std::endl;
	return 0;
}

