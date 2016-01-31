#pragma once

struct Calculator
{
	Calculator() = delete;

	// parses expressions like "7 / 2 + 12 - 3 * 4 + 17 - 2 * 7"
	// calculates and returns result.
	static float parseExpr(std::string_view &ref);

private:
	static float parseSymbol(std::string_view &ref);
	static float parseFloat(std::string_view &ref);
	static float parseExprMul(std::string_view &ref);
	static float parseExprSum(std::string_view &ref);
	static void skipSpaces(std::string_view &ref);
};

