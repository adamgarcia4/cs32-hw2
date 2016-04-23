

#include <iostream>
#include <string>
#include <stack>
using namespace std;
//infix to postfix conversion

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
	//string infix;
	//cerr << "enter infix string: " << endl;
	//getline(cin, infix);
	//cerr << endl;
	//
	//string postfix = ""; //initialized postfix to empty
	string postfix = "";
	bool answer;
	evaluate("!F", postfix, answer);
	cerr << "Answer is: " << endl << answer << endl;

	//infixToPostfix("(T|F)|(F&T)", postfix);
	
	cin.ignore(1000, '\n');

	/*
	bool result = false;
	string infix;
	getline(cin, infix);
	string postfix = ""; //initialized postfix to empty

	//evaluate(infix, postfix, result);
	*/

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
	infixToPostfix(infix, postfix);//postfix now has valid syntax
	result = evalPostfix(postfix);
	return 0;

	//if infix is syntactically valid infix boolean expression
		//set postfix to the postfix form of that expression
		//set result to the value of that expression
		//return 0
	//if not syntactically valid expression
	//return 1
	//in this case, postfix may or may not be changed, but result must be unchanged.

	return 0;
}

//returns true if precedence of curr <= stack top
bool currPrecedence(char curr, char top)
{
	if (curr != '&' || curr != '!' || curr != '|' || top != '&' || top != '!' || top != '|')
	{
		cerr << "either curr or top not correct syntax." << endl;
		return false;
	}

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
	stack<char> opStack; //initialized operator stack to empty
	cerr << "Infix is: " << endl << infix << endl;

	for (int i = 0; i < infix.size(); i++) //for each ch in infix string
	{
		switch (infix[i]) //switch ch
		{
		case 't':
		case 'T':
		case 'f':
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
			cerr << "Not formatted properly" << endl;
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
		else //ch is a binary operator like !/&/| in that order of precedence.
		{
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
				opStack.push(operand1);
				opStack.push(!operand2);
				
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