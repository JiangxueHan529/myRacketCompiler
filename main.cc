/*
 * "Compiler" project for HaverRacket
 *  Translate a subset of Racket into HERA
 *
 * To run this project and run the program tests/01-multiply.hrk, use the command:
 *   Debug/Compiler-C++-withgitandfiles < tests/01-multiply.hrk | tee Compiler.out
 * and then run the HERA program with the command
 *   HERA-C-Run Compiler.out
 */

#include <iostream>
#include <cstdlib>
#include "scannerDemo.h"
#include "parser.h"
#include "AST.h"
#include "ContextInfo.h"
#include "hc_list_helpers.h" // ez_list

using std::cout;
using std::cerr;
using std::endl;
using std::string;

#include "streams.h"

// to change trace output, compile with
//   e.g. -DTRACE_OUTPUT_HERE="./my-trace-output.txt"
//     or -DTRACE_OUTPUT_HERE="/dev/stderr" # (on linux), to throw away trace output
//     or -DTRACE_OUTPUT_HERE="/dev/stderr" # (on linux), to always use cerr
//     or -DTRACE_OUTPUT_HERE=(getenv("HAVERRACKET_TRACE")?getenv("HAVERRACKET_TRACE"):"/dev/stderr")
//        # that last, the default (I hope) should allow run-time selection via e.g.,
//        HAVERRACKET_TRACE=my-trace-output1.txt Debug/Compiler-C++
//
//  similarly for -DPROMPT_OUTPUT_HERE, which defaults to getenv("HAVERRACKET_PROMPT")
//    note that prompt is not currently used, though

#if ! defined TRACE_OUTPUT_HERE
#define TRACE_OUTPUT_HERE (getenv("HAVERRACKET_TRACE")?getenv("HAVERRACKET_TRACE"):"/dev/stderr")
#endif
#if ! defined PROMPT_OUTPUT_HERE
#define PROMPT_OUTPUT_HERE (getenv("HAVERRACKET_PROMPT")?getenv("HAVERRACKET_PROMPT"):"/dev/stderr")
#endif

#include <fstream>  /* needed for ofstream below */
std::ofstream _HaverRacket_trace(TRACE_OUTPUT_HERE);
std::ostream &trace  = _HaverRacket_trace;
std::ofstream _HaverRacket_prompt(PROMPT_OUTPUT_HERE);
std::ostream &prompt = _HaverRacket_prompt;

#if ! defined AbstractSyntaxTest
#define AbstractSyntaxTest build_example1   /* this lets us use a different test easily with a special command line */
#endif

ParserResult AbstractSyntaxTest();

int main(int numberOfCommandLineArguments, char *theCommandLineArguments[])
{
	try {
		bool testScannerInstead = false;
		if (numberOfCommandLineArguments == 2 && theCommandLineArguments[1] == string("testScannerInstead")) {
			trace << "Testing Scanner instead." << endl;
			testScannerInstead = true;
		}

		if (testScannerInstead) {
			cout << "Demonstrating lexical scanner. Enter tokens followed by <EOF>." << endl;
			scannerDemo();
		} else {
			if (!getenv("HAVERRACKET_TEST_CODE_HERA") ||
			    getenv("HAVERRACKET_TEST_CODE_HERA") == string("#t"))
			{
				try {
					ParserResult example1 = AbstractSyntaxTest();

					trace << "confirming codegen basic functionality on test example1:" << endl;
					string code = generateFullHERA(example1);
					trace << code << endl;
					delete example1;  // we're done with example1 now.

				} catch (const char *message) {
					cerr << "code generation confirmation test threw exception: " << message << endl;
					return 2;
				}
			}

			try {
				ParserResult AST = matchStartSymbolAndEOF();
//				trace << "Completed Parsing, got AST: " << AST.toCode() << endl;
				try {
					trace << "Now generating code: " << endl;
					cout << generateFullHERA(AST) << endl;
#if FREE_AST_VIA_DESTRUCTORS
					delete AST;
#endif
				} catch (const char *message) {
					cerr << "eval threw exception (typically an unhandled case): " << message << endl;
					return 4;
				}
			} catch (const char *message) {
				cerr << "that's odd, parser threw exception: " << message << endl;
				return 3;
			}
		}

		return 0;  // indicate successful translation if no exit with non-0 before this
	} catch (...) {
		cerr << "Yikes! Uncaught exception" << endl;
		return 66;
	}
}


	    

ParserResult build_example1()
{
	ExprNode *product = new ArithmeticNode("*", HaverfordCS::ez_list<ExprNode *>(new IntLiteralNode(3), new IntLiteralNode(7)));
	//return product;
/*
  NOTE that the starter files ExprNode classes do _not_ support the following due to memory allocation techniques,
    though it might seem at first to work:
*/
	return new ArithmeticNode("+", HaverfordCS::ez_list<ExprNode *>(product, product));
	// return new ComparisonNode("<=", product, product);
}

