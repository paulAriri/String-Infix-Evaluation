// CS321PaulAririAssignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <string>
using namespace std;

string infixToPostfix(string expression);
int precOper(char oper);
bool IsOperator(char C);
int evalPostfix(string postfix);

int main()
{
    string infixOper;

	char continueOper = 'y';

	while (continueOper != 'n') {

		cout << "******************************" << endl;
		cout << "** Enter an Infix Operation **" << endl;
		cout << "******************************" << endl;

		getline(cin, infixOper);

		string postfix = infixToPostfix(infixOper);

		cout << "The postfix expression is: " << postfix << endl;

		if (postfix != "Wrong Input Error... Try again") {
			cout << "The evaluated calculation is: " << evalPostfix(postfix) << endl;
		}
		
		cout << "Do you want to continue? Input y for Yes and n for No!" << endl;

		cin >> continueOper;

		while (continueOper != 'y' && continueOper != 'n') {
			cout << "Wrong Input... Input y for Yes and n for No!" << endl;
			cin >> continueOper;
		}

		cout << endl;

		cin.ignore();
	}

	cout << "You successfully exited";

    return 0;
}

string infixToPostfix(string infixOper)
{
	stack<char> S;
	string postfix = "";

	for(int i = 0; i < infixOper.length(); i++) {
		if (infixOper[i] == ' ' || infixOper[i] == ',') continue;

		else if (IsOperator(infixOper[i]))
		{
			while (!S.empty() && S.top() != '(' && (precOper(S.top()) > precOper(infixOper[i])))
			{
				postfix += S.top();
				S.pop();
			}
			S.push(infixOper[i]);
		}

		else if (isdigit(infixOper[i]))
		{
			postfix += infixOper[i];
		}
		else if (infixOper[i] == '(')
		{
			S.push(infixOper[i]);
		}

		else if (infixOper[i] == ')')
		{
			while (!S.empty() && S.top() != '(') {
				postfix += S.top();
				S.pop();
			}
			if (!S.empty()) S.pop();
			else return "Wrong Input Error... Try again";
		}
		else if (!isdigit(infixOper[i])) {
			return "Wrong Input Error... Try again";
		}

		if (IsOperator(infixOper[i + 1])) {
			postfix += "_";
		}
	}

	while (!S.empty()) {
		postfix += S.top();
		S.pop();
	}

	return postfix;
}

bool IsOperator(char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/')
		return true;

	return false;
}

int precOper(char oper) {
	if (oper == '-' || oper == '+') {
		return 1;
	}
	else return 2;
}

int evalPostfix(string postfix) {
	stack<int> s;

	for (int i = 0; i < postfix.length(); i++)
	{
		if (postfix[i] == '_') continue;

		else if (isdigit(postfix[i]))
		{
			int num = 0;

			while (isdigit(postfix[i]))
			{
				int digit = postfix[i] - '0';
				num = (num * 10) + digit;
				i++;
			}
			i--;

			s.push(num);
		}

		else
		{
			int val1 = s.top();
			s.pop();
			int val2 = s.top();
			s.pop();

			switch (postfix[i])
			{
				case '+': s.push(val2 + val1); break;
				case '-': s.push(val2 - val1); break;
				case '*': s.push(val2 * val1); break;
				case '/': s.push(val2 / val1); break;
			}
		}
	}

	return s.top();
}