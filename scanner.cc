#include <iostream>
#include <logic.h>
#include "scanner.h"

#if ! defined USE_YYLEX
#define USE_YYLEX 1  /* Use the stuff from scanner-regexp.l by default */
#endif

using namespace std;

int tokenCount = 0;  // not static because the .l file needs it too
static bool endOfInput = false;
static bool calledGetNextTokenAlready = false;
static string current = "";
static kindOfToken currentKind;

// some things built into scanner-regexp.cc by the flex system:
extern int yylex();
extern char *yytext;  // C-style string


string currentToken()
{
	precondition(calledGetNextTokenAlready);
	precondition(tokenAvailable());
	
	return current;
}
enum kindOfToken currentTokenKind()
{
	precondition(calledGetNextTokenAlready);
	precondition(tokenAvailable());

	return currentKind;
}

bool tokenAvailable()
{
	precondition(calledGetNextTokenAlready);
	
	return !endOfInput;
}

int  tokenNumber()
{
	return tokenCount;
}

void getNextToken()
{
	if (calledGetNextTokenAlready && endOfInput) return;  // No soup for you!
	
	calledGetNextTokenAlready = true;
#if USE_YYLEX
	/// This interfaces with scanner-regexp.cc
	/// remember to update it from scanner-regexp.l if that is changed!
	currentKind = kindOfToken(yylex()); // yylex thinks it could return any int but we know better
	if (currentKind == 0) {
		endOfInput = true;
		current      = "";
	} else {
		current      = yytext;
	}
#else
	/// HERE IS THE OLD CODE, before I tried lex
	if (endOfInput || !cin) {
		endOfInput = true;
	} else {
		cin >> current;
		if (cin && current != "<EOF>") {
			tokenCount++;
		} else {
			endOfInput = true;
		}
	}
#endif
}

void scannerError()
{
	cerr << "Error: illegal token: '" << yytext << "'\n";
}
