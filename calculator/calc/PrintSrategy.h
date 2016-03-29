#pragma once
#include "stdafx.h"

class PrintStrategy
{
public:
	PrintStrategy(std::ostream & outputStream);
	virtual ~PrintStrategy() = default;
	virtual void printNumber(double number) const = 0;
	virtual void printFunctionName(std::string functionName) const = 0;
	virtual void printAddition() const = 0;
	virtual void printSubstraction() const = 0;
	virtual void printMultiplication() const = 0;
	virtual void printDivision() const = 0;
protected:
	std::ostream & m_outputStream;
};