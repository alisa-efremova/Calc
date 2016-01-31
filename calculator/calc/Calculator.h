#pragma once

struct Calculator
{
	Calculator() = delete;

	// parses expressions like "7 / 2 + 12 - 3 * 4 + 17 - 2 * 7"
	// calculates and returns result.
	static double parseExpr(std::string_view &ref);

private:
	static double parseSymbol(std::string_view &ref);
	static double parseDouble(std::string_view &ref);
	static double parseExprMul(std::string_view &ref);
	static double parseExprSum(std::string_view &ref);
	static void skipSpaces(std::string_view &ref);
	static double parseFunction(std::string_view &ref);
};

