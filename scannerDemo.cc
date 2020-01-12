#include <iostream>
#include "scanner.h"
#include "scannerDemo.h"

using std::cout;
using std::endl;

void scannerDemo()
{
	while (getNextToken(), tokenAvailable()) {
		cout << "Token number " << tokenNumber() << " is ";
		cout << "'" << currentToken() << "'";
		cout << ", which is token kind " << currentTokenKind() << endl;
	}
	cout << "Reached end-of-file, now stopping!" << endl;
}
