#pragma once

struct Calculator
{
	Calculator() = delete;

	// parses expressions like "7 / 2 + 12 - 3 * 4 + 17 - 2 * 7"
	// calculates and returns result.
	static float parseExpr(boost::string_ref &ref);

private:
	static float parseFloat(boost::string_ref &ref);
	static float parseExprMul(boost::string_ref &ref);
	static float parseExprSum(boost::string_ref &ref);
	static void skipSpaces(boost::string_ref &ref);
};

