#pragma once
#include "PrintSrategy.h"

class StackMachinePrintStrategy : public PrintStrategy
{
public:
	StackMachinePrintStrategy(std::ostream & outputStream);
	virtual void printNumber(double number) const override;
	virtual void printFunctionName(std::string functionName) const override;
	virtual void printAddition() const override;
	virtual void printSubstraction() const override;
	virtual void printMultiplication() const override;
	virtual void printDivision() const override;
};

