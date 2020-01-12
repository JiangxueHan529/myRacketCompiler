#include <string>

class ContextInfo {
public:
	ContextInfo(); // create an empty one, appropriate for the TOP of a parse tree

	ContextInfo evalThisAfter() const; // create another context for something to be evaluated later

	std::string getReg() const;
 private:
	// "myRegNumber" will tell each expression what register number they should use for their result
	//  should generally be different for the subexpressions of a node,
	//  and if X is evalualuated before Y, it should have a higher number.

	ContextInfo(int myRegNum);  // called by e.g. evalThisFirst, to build new contexts
	int myRegNumber;
};
