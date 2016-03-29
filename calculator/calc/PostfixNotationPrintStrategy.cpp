#include "stdafx.h"
#include "PostfixNotationPrintStrategy.h"


PostfixNotationPrintStrategy::PostfixNotationPrintStrategy(std::ostream & ouputStream)
	:PrintStrategy(ouputStream)
{
}

void PostfixNotationPrintStrategy::printNumber(double number) const
{
	m_outputStream << number << " ";
}

void PostfixNotationPrintStrategy::printFunctionName(std::string functionName) const
{
	m_outputStream << functionName;
}

void PostfixNotationPrintStrategy::printAddition() const
{
	m_outputStream << "+ ";
}

void PostfixNotationPrintStrategy::printSubstraction() const
{
	m_outputStream << "- ";
}

void PostfixNotationPrintStrategy::printMultiplication() const
{
	m_outputStream << "* ";
}

void PostfixNotationPrintStrategy::printDivision() const
{
	m_outputStream << "/ ";
}

