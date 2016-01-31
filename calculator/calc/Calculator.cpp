#include "stdafx.h"
#include "Calculator.h"

float Calculator::parseExpr(std::string_view &ref)
{
	float result = parseExprSum(ref);
	if (!ref.empty())
	{
		return std::numeric_limits<float>::quiet_NaN();
	}

	return result;
}


float Calculator::parseExprSum(std::string_view &ref)
{
	float value = parseExprMul(ref);
	while (true)
	{
		skipSpaces(ref);
		if (!ref.empty() && ref[0] == '+')
		{
			ref.remove_prefix(1);
			value += parseExprMul(ref);
			std::cout << "+ ";
		}
		else if (!ref.empty() && ref[0] == '-')
		{
			ref.remove_prefix(1);
			value -= parseExprMul(ref);
			std::cout << "- ";
		}
		else
		{
			break;
		}
	}

	return value;
}

float Calculator::parseExprMul(std::string_view &ref)
{
	float value = parseSymbol(ref);
	while (true)
	{
		skipSpaces(ref);
		if (!ref.empty() && ref[0] == '*')
		{
			ref.remove_prefix(1);
			value *= parseSymbol(ref);
			std::cout << "* ";
		}
		else if (!ref.empty() && ref[0] == '/')
		{
			ref.remove_prefix(1);
			value /= parseSymbol(ref);
			std::cout << "/ ";
		}
		else
		{
			break;
		}
	}

	return value;
}

float Calculator::parseSymbol(std::string_view &ref)
{
	float value = 0;
	skipSpaces(ref);
	if (!ref.empty() && ref[0] == '(')
	{
		ref.remove_prefix(1);
		value = parseExprSum(ref);
		skipSpaces(ref);
		if (!ref.empty() && ref[0] == ')')
		{
			ref.remove_prefix(1);
			return value;
		}
		else
		{
			return std::numeric_limits<float>::quiet_NaN();
		}
	}
	else
	{
		return parseFloat(ref);
	}
}

float Calculator::parseFloat(std::string_view &ref)
{
	float value = 0;
	bool parsedAny = false;
	skipSpaces(ref);
	while (!ref.empty() && std::isdigit(ref[0]))
	{
		parsedAny = true;
		const int digit = ref[0] - '0';
		value = value * 10.0f + float(digit);
		ref.remove_prefix(1);
	}

	if (!parsedAny)
	{
		return std::numeric_limits<float>::quiet_NaN();
	}

	if (ref.empty() || (ref[0] != '.'))
	{
		std::cout << value << " ";
		return value;
	}

	ref.remove_prefix(1);
	float factor = 1.f;
	while (!ref.empty() && std::isdigit(ref[0]))
	{
		const int digit = ref[0] - '0';
		factor *= 0.1f;
		value += factor * float(digit);
		ref.remove_prefix(1);
	}

	std::cout << value << " ";
	return value;
}

void Calculator::skipSpaces(std::string_view &ref)
{
	size_t i = 0;
	while (i < ref.size() && std::isspace(ref[i]))
	{
		++i;
	}
	ref.remove_prefix(i);
}
