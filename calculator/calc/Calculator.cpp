#include "stdafx.h"
#include "Calculator.h"

Calculator::Calculator(std::unique_ptr<PrintStrategy> && printStrategy)
	:m_printStrategy(move(printStrategy))
{
}

Calculator::~Calculator()
{
}

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
			m_printStrategy->printAddition();
		}
		else if (!ref.empty() && ref[0] == '-')
		{
			ref.remove_prefix(1);
			value -= parseExprMul(ref);
			m_printStrategy->printSubstraction();
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
			m_printStrategy->printMultiplication();
		}
		else if (!ref.empty() && ref[0] == '/')
		{
			ref.remove_prefix(1);
			value /= parseSymbol(ref);
			m_printStrategy->printDivision();
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
	else if (!ref.empty() && !std::isdigit(ref[0]) && ref[0] != '-')
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
	try
	{
		std::string_view partStr = ref.substr(0, 3);

		if (partStr == std::string_view("sin"))
		{
			ref.remove_prefix(3);
			m_printStrategy->printFunctionName("sin");
			return sin(ParseArguments(ref) * M_PI / 180);
		}
		else if (partStr == std::string_view("cos"))
		{
			ref.remove_prefix(3);
			m_printStrategy->printFunctionName("cos");
			return cos(ParseArguments(ref) * M_PI / 180);
		}
		else
		{
			std::string_view partStr = ref.substr(0, 4);

			if (partStr == std::string_view("sqrt"))
			{
				ref.remove_prefix(4);
				m_printStrategy->printFunctionName("sqrt");
				return sqrt(ParseArguments(ref));
			}
		}
	}
	catch(const std::out_of_range&)
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	
	return std::numeric_limits<double>::quiet_NaN();
}

double Calculator::ParseArguments(std::string_view &ref)
{
	double value = 0;
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
	else
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
}

double Calculator::parseDouble(std::string_view &ref)
{
	double value = 0;
	bool isNegative = false;
	bool parsedAny = false;

	skipSpaces(ref);
	if (!ref.empty() && ref[0] == '-')
	{
		isNegative = true;
		ref.remove_prefix(1);
	}
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

	if (isNegative)
	{
		value *= -1;
	}

	if (ref.empty() || (ref[0] != '.'))
	{
		m_printStrategy->printNumber(value);
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

	m_printStrategy->printNumber(value);
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
