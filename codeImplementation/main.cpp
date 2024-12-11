//Main
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

using namespace std;

extern bool processExpression(const string& expression);
extern vector<string> parse(string);
extern double evaluator(vector<string>&);
extern double conv_float(const string&);

int main() {
	// Get input from user in while loop
	// If input is 'quit,' exit the loop
	// Otherwise, pass it to lexer
	while (true) { // takes in user input
		cout << "Enter an arithmetic expression (or 'quit' to quit): ";
		string input;
		getline(cin, input);

		// Check for 'quit' condition
		if (input == "quit" || input == "Quit") {
			cout << "Quitting calculator..." << endl;
			break;
		}

		try {
			if (!processExpression(input)) {
                // If expression is invalid, continue to next iteration
				// calling lexer
				continue;
			
			}
			// parse user's expression to postfix notation
			// calls parser
			vector<string> postfix = parse(input);

			// evaluate the postfix notation
			// calls evaluator
			double result = evaluator(postfix);
			cout << "Result: " << result << endl;
		}
		// handle specific error messages from stack or evaluator
		catch (const char* errorMsg) {
			cerr << "Error: " << errorMsg << endl;
		}
		// handle any other standard exceptions
		catch (const exception& e) {
			cerr << "Unexpected error: " << e.what() << endl;
		}
	}
	return 0;
}