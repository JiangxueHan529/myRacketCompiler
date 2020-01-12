#ifndef PARSER_H_
#define PARSER_H_


#include "AST.h"

// The typedef below makes the name "translatedResult"
//  mean a "Tree" object from our Expr_Node type heirarchy.
typedef ExprNode *ParserResult;

ParserResult matchStartSymbolAndEOF();

#endif /*PARSER_H_*/
