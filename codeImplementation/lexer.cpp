//Lexer
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

//Function declaration for the parser
extern vector<string> parse(string expression);

//Function to validate the arithmetic expression
bool validateExpression(const string& expression) {
    int parenthesesBalance = 0;
    bool lastWasOperator = false;
    bool expectOperand = true; //Start by expecting an operand

    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];

        if (isspace(ch)) {
            continue; //Ignore whitespace
        } else if (isdigit(ch) || ch == '.') {
            expectOperand = false; //Number encountered
            lastWasOperator = false;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
            if (ch == '*' && i + 1 < expression.length() && expression[i + 1] == '*') {
                if (lastWasOperator || expectOperand) {
                    return false; //Invalid operator placement
                }
                ++i;
            } else if (lastWasOperator || expectOperand) {
                return false; //Invalid operator placement
            }
            lastWasOperator = true;
            expectOperand = true;
        } else if (ch == '(') {
            parenthesesBalance++;
            expectOperand = true; //Operand expected after '('
        } else if (ch == ')') {
            parenthesesBalance--;
            if (parenthesesBalance < 0 || lastWasOperator) {
                return false; //Unbalanced parentheses or invalid placement
            }
            lastWasOperator = false;
        } else {
            return false; //Invalid character
        }
    }

    //Ensure no unbalanced parentheses and the last character isn't an operator
    return parenthesesBalance == 0 && !lastWasOperator;
}

//Function to process the expression and pass it to the parser
bool processExpression(const string& expression) {
    if (validateExpression(expression)) {
        //Send to the parser if valid
        parse(expression);
        return true;
    } else {
        cerr << "Invalid arithmetic expression!" << endl;
        return false;
    }
}
