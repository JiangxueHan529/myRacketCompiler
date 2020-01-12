#ifndef AST_H_
#define AST_H_

#include <string>
#include <hc_list.h>


/*
 *  This file defines the heirarchy of different kinds of AST nodes.
 *  Currently we have:
 *    ExprNode (an "interface" class for expressions, with the following concrete subclasses ("implementers" of the interface):
 *	IntLiteralNode(int value)
 *	ComparisonNode(std::string op, ExprNode *lhs, ExprNode *rhs)
 *	ArithmeticNode(std::string op, list<ExprNode *>)
 *	VarUseNode(std::string name)
 *	CallNode(std::string name, HaverfordCS::list<ExprNode *>arguments)
 *
 *  The "generateHERA" methods are usually called by calling generateFullHERA on the root,
 *      which puts "CBON" at the start.
 */

#if ! defined FREE_AST_VIA_DESTRUCTORS
#define FREE_AST_VIA_DESTRUCTORS true
#endif

// C++ Usage Note:
// The empty class definition of ContextInfo below lets us declare "const ContextInfo &" parameters
//   without having to define the whole class here, which is fine because, at this point,
//   we don't care much about what's in it ... we just need to know that there's some way
//   to pass information down to the subtrees as we evaluate them.


// Define the information will we need to pass down the tree as we generate code, see ContextInfo.h
class ContextInfo;


// C++ Usage Note:
//
// The word "virtual" is needed in C++ when inheritance is use,
//   to explicitly tell the compiler that we might override a function in a subclass
// Java has the correct default of allowing this, and the keyword "final" prevents it.
//   Many C++ compilers fail to complain if you forget the word "virtual" and override a method anyway :-(
//
// Putting "= 0" at the end of a virtual function declaration means
//   that the method _must_ be overridden in subclasses
//
// Classes with virtual functions and (in subclasses) data with destructors need to have
//  virtual destructors, to help the C++ compiler be sure the right data destructors are called


// Class ExprNode is an interface that defines the methods that all
//   expression nodes in our AST will provide
// C++ does not have Java's "interface" keyword, so instead
//   we just create a superclass with no data and all functions virtual

class ExprNode {
public:
	ExprNode();           // just used for memory allocation labs, to print trace information
	virtual ~ExprNode();  // used for actual memory allocation, sometimes, and for tracing
	void increaseCounter();
	void decreaseCounter();
	bool zeroCounter();
	virtual std::string generateHERA(const ContextInfo &info) const = 0;
	// virtual typeInfo type() = 0;  // type info not required in 2019
protected:
	mutable int counter;
};

std::string generateFullHERA(ExprNode *presumedRoot);



// Now, the various specific kinds of expressions we might have:

class IntLiteralNode : public ExprNode {
	public:
		IntLiteralNode(int value);
		~IntLiteralNode();  // just used for trace output

		std::string generateHERA(const ContextInfo &info) const;
	private:
		int v;  // the value
};


class ComparisonNode : public ExprNode {  // <= etc., _inherently_binary_ in HaverRacket
	public:
		ComparisonNode(std::string op, ExprNode *lhs, ExprNode *rhs);
#if FREE_AST_VIA_DESTRUCTORS
		~ComparisonNode();
#endif
		std::string generateHERA(const ContextInfo &info) const;
	private:
		std::string o;
		ExprNode *left;
		ExprNode *right;
};

class ArithmeticNode : public ExprNode {  // +, *, -, etc.
	public:
		ArithmeticNode(std::string op, HaverfordCS::list<ExprNode *>);
#if FREE_AST_VIA_DESTRUCTORS
		~ArithmeticNode();
#endif
	
		std::string generateHERA(const ContextInfo &info) const;
	private:
		std::string o;
		HaverfordCS::list<ExprNode *>subexps;
};


/*
   This represents the use of an identifier as an expression, e.g. the x in (* x 6).
   Note that identifiers also exist in variable declarations, e.g. (let ((x 7)) ... )
     but the x there doesn't count as an _expression_ since we're not asking for its value.
 */

class VarUseNode : public ExprNode {
	public:
		VarUseNode(std::string name);
		~VarUseNode();
	
		std::string generateHERA(const ContextInfo &info) const;
	private:
		std::string n;
};


class CallNode : public ExprNode {
	public:
		CallNode(std::string funcName, HaverfordCS::list<ExprNode *>arguments);
#if FREE_AST_VIA_DESTRUCTORS
		~CallNode();
#endif

		std::string generateHERA(const ContextInfo &info) const;
	private:
		std::string n;  // the name
		HaverfordCS::list<ExprNode *>argList;
};


#endif /*AST_H_*/
