#include "stdafx.h"
#include "StackMachinePrintStrategy.h"

using namespace std;

const string PUSH      = "push";
const string ADD       = "add";
const string SUBSTRACT = "sub";
const string MULTIPLY  = "mul";
const string DIVIDE    = "div";

StackMachinePrintStrategy::StackMachinePrintStrategy(std::ostream & outputStream)
	:PrintStrategy(outputStream)
{
}

void StackMachinePrintStrategy::printNumber(double number) const
{
	m_outputStream << PUSH << " " << number << endl;
}

void StackMachinePrintStrategy::printFunctionName(std::string functionName) const
{
	m_outputStream << functionName << endl;
}

void StackMachinePrintStrategy::printAddition() const
{
	m_outputStream << ADD << endl;
}

void StackMachinePrintStrategy::printSubstraction() const
{
	m_outputStream << SUBSTRACT << endl;
}

void StackMachinePrintStrategy::printMultiplication() const
{
	m_outputStream << MULTIPLY << endl;
}

void StackMachinePrintStrategy::printDivision() const
{
	m_outputStream << DIVIDE << endl;
}