

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;
//infix to postfix conversion

bool isValidInfix(string infix);

//Both infix and postfix are syntactically valid.  So swap.
bool infixToPostfix(string infix, string& postfix);

bool evalPostfix(string postfix);
bool evalOperand(char ch);
bool isOperand(char ch);

//	 Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.)
int evaluate(string infix, string& postfix, bool& result);

bool currPrecedence(char curr, char top);

int main()
{
	string pf;
	bool answer;

	
	
	//cerr<<isValidInfix("!T"); //0
	//cerr << isValidInfix(")T("); //0
	//cerr << isValidInfix("      "); //0
	//cerr << isValidInfix("!&T&F"); //0

	//cerr << isValidInfix("T| F");
	
	//cerr << isValidInfix("T|");
	//cerr << isValidInfix("F F");
	//cerr << isValidInfix("TF");
	//cerr << isValidInfix("()");
	//cerr << isValidInfix("T(F|T)");
	//cerr << isValidInfix("T(&T)");
	//cerr << isValidInfix("(T&(F|F)");
	//cerr << isValidInfix("");
	//cerr << isValidInfix("F  |  !F & (T&F) ");
	//cerr << isValidInfix("");
	//cerr << isValidInfix(" F  ");
	//cerr << isValidInfix("((T))");
	

	


	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|"  &&  answer);
	assert(evaluate("T|", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("T(F|T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F|F)", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&|" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	cout << "Passed all tests" << endl;

	////string infix;
	////cerr << "enter infix string: " << endl;
	////getline(cin, infix);
	////cerr << endl;
	////
	////string postfix = ""; //initialized postfix to empty
	//string postfix = "";
	//bool answer;
	//evaluate("T|", postfix, answer);
	//cerr << "Answer is: " << endl << answer << endl;

	////infixToPostfix("(T|F)|(F&T)", postfix);
	//


	///*
	//bool result = false;
	//string infix;
	//getline(cin, infix);
	//string postfix = ""; //initialized postfix to empty

	////evaluate(infix, postfix, result);
	//*/


	cin.ignore(1000, '\n');
}

//	 Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.)
int evaluate(string infix, string& postfix, bool& result)
{
	if (isValidInfix(infix))
	{
		infixToPostfix(infix, postfix);//postfix now has valid syntax
		result = evalPostfix(postfix);
		return 0;
	}
	else
	{
		return 1;
	}
}

bool isValidInfix(string infix)
{

	//if empty, false
	int openParend = 0;
	int diffCount = 0;
	int spaceCount = 0;
	int operandCount = 0;
	char lastChar = '/'; //flag which tells if last was an operator or operand.
	for (int i = 0; i < infix.length(); i++) //iterate through every pos
	{
		switch (infix[i])
		{
		case ' ':
			spaceCount++;
			continue;
		case '(':
			openParend++;
			if (lastChar == 'T' || lastChar == 'F')
				return false;
			lastChar = infix[i];
			break;
		case ')':
			openParend--;
			lastChar = infix[i];
			if (openParend < 0) //accounts for a closed parend first.
				return false;
			break;
		case 'T':
		case 'F':
			if (lastChar == 'T' || lastChar == 'F') //if repeating T/F.
				return false;
			diffCount++;
			operandCount++;
			lastChar = infix[i];
			break;
		case '!':
			lastChar = infix[i];
			break;
		case '&':
		case '|':
			if (lastChar == '&' || lastChar == '|' || lastChar=='!'||lastChar=='(') //repeating operator.
				return false;
			lastChar = infix[i];
			diffCount--;
			break;			
		default:
			return false;
			break;
		}
	}
	if (spaceCount == infix.size()) //accounts for a string of all spaces
		return false;
	if (operandCount <= 0)//need at least one operand.
		return false;

	if (infix[infix.size() - 1] == '&' || infix[infix.size() - 1] == '|')
		return false;
	if (infix[0] == '&' || infix[0] == '|')
		return false;

	if (openParend != 0) //accounts for mismatched numbers of parends.
		return false;
	return true;

}

//returns true if precedence of curr <= stack top
bool currPrecedence(char curr, char top)
{
	//if (curr != '&' || curr != '!' || curr != '|' || top != '&' || top != '!' || top != '|')
	//{
	//	cerr << "either curr or top not correct syntax." << endl<<curr <<endl<< top << endl;
	//	return false;

	//}

	int currRating, topRating;

	switch (curr)
	{
	case '!':
		currRating = 3;
		break;
	case '&':
		currRating = 2;
		break;
	case '|':
		currRating = 1;
		break;
	default:
		cerr << "curr not a valid operator";
		break;
	}

	switch (top)
	{
	case '!':
		topRating = 3;
		break;
	case '&':
		topRating = 2;
		break;
	case '|':
		topRating = 1;
		break;
	default:
		cerr << "top not a valid operator";
		break;
	}

	return (currRating <= topRating);
		//returns true if precedence of curr <= stack top


	return 0;
}

bool infixToPostfix(string infix, string& postfix)
{
	postfix = "";
	stack<char> opStack; //initialized operator stack to empty
	cerr << "Infix is: " << endl << infix << endl;

	for (int i = 0; i < infix.size(); i++) //for each ch in infix string
	{
		switch (infix[i]) //switch ch
		{
		case ' ':
			break;
		case 'T':
		case 'F':
			postfix += infix[i]; //append ch to end of postfix
			break;

		case '(':
			opStack.push(infix[i]); //push ch onto op stack.
			break;

		case ')':
			while (opStack.top() != '(')
			{
				postfix += opStack.top(); //append the stack top to postfix
				opStack.pop(); // pop stack
			}
			opStack.pop(); // remove the '('
			break;
		case '&':
		case '|':
		case '!':
			while (!opStack.empty() && opStack.top() != '(' && currPrecedence(infix[i], opStack.top()))
			{
				postfix += opStack.top();
				opStack.pop();
			}
			opStack.push(infix[i]);
			break;

		default: //operand case.  Like a T/F
			cerr << "Not formatted properly" << infix[i]<< "hi"<<endl;
			return -1;
			break;
		}


		//cerr << infix[i];
		//access with infix[i]
	}
	while (!opStack.empty())
	{
		postfix += opStack.top();
		opStack.pop();
	}

	cerr << "Postfix is: " << endl << postfix << endl;

}

bool evalPostfix(string postfix)
{
	stack<bool> opStack; //initialize operand stack to empty.
	
	for (int i = 0; i < postfix.size(); i++) //For each character ch in the postfix string
	{
		if (isOperand(postfix[i])) //if we have T/F
		{
			opStack.push(evalOperand(postfix[i]));
		}
		else //ch is a binary operator like !/&/|
		{
			if (postfix[i] == '!')
			{
				bool operand3 = opStack.top();
				opStack.pop();
				opStack.push(!operand3);
				continue;
			}
			bool operand2 = opStack.top();
			opStack.pop();
			bool operand1 = opStack.top();
			opStack.pop();
			if (postfix[i] == '&')
			{
				opStack.push(operand2 && operand1);
			}
			else if (postfix[i] == '|')
			{
				opStack.push(operand2 || operand1);
			}
			else if (postfix[i] == '!')
			{
				cerr << "Encounterd an !" << endl;
			}
			else
			{
				cerr << "Encountered a: " << postfix[i] << endl;
			}
		}
	}

	return opStack.top();


	//return false;
}

//returns true if the input character is an operand
bool isOperand(char ch)
{
	if (ch == 'T' || ch == 't' || ch == 'F' || ch == 'f')
		return true;
	return false;
}

bool evalOperand(char ch)
{
	switch (ch)
	{
	case 'T':
	case 't':
		return true;
		break;
	case 'F':
	case 'f':
		return false;
		break;
	default:
		break;
	}
}