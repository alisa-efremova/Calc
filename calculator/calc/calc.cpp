#include "stdafx.h"
#include "Calculator.h"

#include "PostfixNotationPrintStrategy.h"
#include "StackMachinePrintStrategy.h"

#include <fstream>

using namespace std;

int main()
{
	string expr = " (10 + 1) * -1 ";
	string_view ref(expr);
	
	ofstream outputFile("SMinput.txt", ofstream::binary);

	Calculator calculator(make_unique<StackMachinePrintStrategy>(outputFile));
	cout << expr << endl << "result: " << calculator.parseExpr(ref) << endl;
	outputFile.close();
	return 0;
}

