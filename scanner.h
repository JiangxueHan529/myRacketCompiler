#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <string>
#include "scanner-regexp.h"

// A simple lexical scanner

// return the current token
//  precondition:     you have called getNextToken at least once
//                and tokenAvialable did not return false
std::string currentToken();
enum kindOfToken currentTokenKind();

// see if there is a token (return false for end-of-input or the special input <EOF>)
//  precondition: you must have called getNextToken at least once
bool tokenAvailable();

// return the number of tokens scanned so far
// precondition: true
int  tokenNumber();

// advance current token to the next input
// precondition: true
void getNextToken();

#endif //_SCANNER_H_
