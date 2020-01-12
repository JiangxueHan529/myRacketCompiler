#include "AST.h"
#include "ContextInfo.h"
#include "hc_list_helpers.h"
#include "streams.h"

std::string generateFullHERA(ExprNode *presumedRoot)
{
	return "CBON()\n" + presumedRoot->generateHERA(ContextInfo());
}



using std::string;
using std::endl;

string IntLiteralNode::generateHERA(const ContextInfo &context) const
{
	trace << "Entered IntLiteralNode::generateHERA for integer " + std::to_string(v) << endl;
	return "SET(" + context.getReg() + ", " + std::to_string(v) + ")\n";
}

string ComparisonNode::generateHERA(const ContextInfo &context) const
{
	trace << "Entered ComparisonNode::generateHERA for comparison " + o << endl;

	// see arithmetic node for more about the "context" stuff:
	//	trace << "need to compare the result of left-hand-side:\n" << left->generateHERA(context) << endl;
	//	trace << "                        with right-hand-side:\n" << left->generateHERA(context.evalThisAfter()) << endl;

	throw "comparison node code generation not implemented yet";
}

std::string HERA_op(const std::string &AST_op_name)
{
	if (AST_op_name == "+") {
		return "ADD";
	} else if (AST_op_name == "-") {
		return "SUB";
	} else if (AST_op_name == "*") {
		return "MUL";
	} else {
		throw "Internal compiler inconsistency/incompleteness: HERA_op not implemented for " + AST_op_name;
	}
}

string ArithmeticNode::generateHERA(const ContextInfo &context) const
{
	trace << "Entered ArithmeticNode::generateHERA for operator " + o << endl;
	if (length(subexps) != 2) {
		throw "compiler incomplete/inconsistent: generateHERA not implemented for non-binary arithmetic";
	}
	ContextInfo rhsContext = context.evalThisAfter();
	ContextInfo lhsContext = context;  // just named for symmetry
	
	return (first(subexps)->generateHERA(lhsContext) +
		first(rest(subexps))->generateHERA(rhsContext) +
		HERA_op(o)+"("+context.getReg()+", "+lhsContext.getReg()+","+rhsContext.getReg()+")\n");
}

string VarUseNode::generateHERA(const ContextInfo &context) const
{
	trace << "Entered VarUseNode::generateHERA for variable " + n << endl;

	throw "variableUse code generation not implemented yet";
	return "compiler ought not to require a return here, this can't be run";
}

string CallNode::generateHERA(const ContextInfo &context) const
{
	trace << "Entered CallNode::generateHERA for call to " + n << endl;
	
	if (length(argList) != 0 || (n != "exit" && n != "getint")) {
		throw "compiler incomplete/inconsistent: generateHERA for calls only implented for getint and exit";
	}
	// NOTE that calls to exit and getint don't need parameters and don't perturb registers
	return ("MOVE(FP_alt, SP)\nCALL(FP_alt," + n + ")\n"+
		(context.getReg()=="R1"?"":"MOVE("+context.getReg()+", R1)\n"));
}
