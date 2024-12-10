//Main
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "parser.cpp"
#include "evaluator.h"
#include "lexer.cpp"
#include "stack.cpp"

using namespace std;

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
			
			// parse user's expression to postfix notation
			vector<string> postfix = parse(input);

			// evaluate the postfix notation
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