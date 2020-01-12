#include "ContextInfo.h"

// To provide unique register numbers for each subexpression, with leftmost-executed-first
//   we'll start with 1 at the root, make the rightmost child's number same as its parent,
//   and make each other child one more than the sibling to its right.

static const int minRegNum= 1;  // Lowest  register number we're going to use
static const int maxRegNum=10;  // Highest register number we're going to use

ContextInfo::ContextInfo():
	myRegNumber(maxRegNum)
{
}

// Private constructor for use in e.g. evalThisFirst
ContextInfo::ContextInfo(int r):
	myRegNumber(r)
{
}

ContextInfo ContextInfo::evalThisAfter() const
{
	if (myRegNumber <= minRegNum) {
		throw "Out of register numbers, expression to complicated";
	}
	return ContextInfo(this->myRegNumber-1);
}

std::string ContextInfo::getReg() const
{
	return "R"+std::to_string(myRegNumber);
}
