#pragma once
#include "PrintSrategy.h"
#include <memory>

struct Calculator
{
	Calculator(std::unique_ptr<PrintStrategy> && printStrategy);
	~Calculator();

	// parses expressions like "7 / 2 + 12 - 3 * 4 + 17 - 2 * 7"
	// calculates and returns result.
	double parseExpr(std::string_view &ref);

private:
	double parseSymbol(std::string_view &ref);
	double parseDouble(std::string_view &ref);
	double parseExprMul(std::string_view &ref);
	double parseExprSum(std::string_view &ref);
	void skipSpaces(std::string_view &ref);
	double parseFunction(std::string_view &ref);
	double ParseArguments(std::string_view &ref);

	std::unique_ptr<PrintStrategy> m_printStrategy;
};

