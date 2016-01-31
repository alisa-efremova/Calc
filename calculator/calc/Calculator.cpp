#include "stdafx.h"
#include "Calculator.h"

#define PI 3.14159265

double Calculator::parseExpr(std::string_view &ref)
{
	double result = parseExprSum(ref);
	if (!ref.empty())
	{
		return std::numeric_limits<double>::quiet_NaN();
	}

	return result;
}


double Calculator::parseExprSum(std::string_view &ref)
{
	double value = parseExprMul(ref);
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

double Calculator::parseExprMul(std::string_view &ref)
{
	double value = parseSymbol(ref);
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

double Calculator::parseSymbol(std::string_view &ref)
{
	double value = 0;
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
			return std::numeric_limits<double>::quiet_NaN();
		}
	}
	else if (!ref.empty() && !std::isdigit(ref[0]))
	{
		return parseFunction(ref);
	}
	else
	{
		return parseDouble(ref);
	}
}

double Calculator::parseFunction(std::string_view &ref)
{
	if (ref.size() >= 3)
	{
		std::string_view partStr = ref.substr(0, 3);
		
		if (partStr == std::string_view("sin"))
		{
			ref.remove_prefix(3);
			std::cout << "sin";
			double value = parseSymbol(ref);
			if (value != std::numeric_limits<double>::quiet_NaN())
			{
				value = sin(value * PI / 180);
			}
			
			return value;
		}
	}
	
	return std::numeric_limits<double>::quiet_NaN();
}

double Calculator::parseDouble(std::string_view &ref)
{
	double value = 0;
	bool parsedAny = false;
	skipSpaces(ref);
	while (!ref.empty() && std::isdigit(ref[0]))
	{
		parsedAny = true;
		const int digit = ref[0] - '0';
		value = value * 10.0f + double(digit);
		ref.remove_prefix(1);
	}

	if (!parsedAny)
	{
		return std::numeric_limits<double>::quiet_NaN();
	}

	if (ref.empty() || (ref[0] != '.'))
	{
		std::cout << value << " ";
		return value;
	}

	ref.remove_prefix(1);
	double factor = 1.f;
	while (!ref.empty() && std::isdigit(ref[0]))
	{
		const int digit = ref[0] - '0';
		factor *= 0.1f;
		value += factor * double(digit);
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
