//Evaluator
#include <iostream>
//#include <iomanip>
#include <string>
#include "stack.cpp"
#include <vector>
#include <cmath>
#include "strToNum.h"
//These are the dependencies that will be utilized throughout the remainder of the evaluator
using namespace std;

double evaluator(vector<string> &vect) {
        Stack<double> stack;
//The stack object will be used to evaluate the expression in postorder
    for (int i = 0; i < (int)vect.size(); i++) {
        cout << vect[i] << endl;
//This for-loop goes through each value of the vector/list from parser
        if (extractNumber(vect[i]) != -999999.99) {
            if (extractNumber(vect[i]) == +0 || extractNumber(vect[i]) == -0) {
                stack.Add(0);
            }
            else {
                stack.Add(extractNumber(vect[i]));
            }
//If the index of the list is a numeric value, it is added to stack
        } else {
            double num2;
            double num1;
            try {
                num2 = stack.Pop();
                num1 = stack.Pop();
            }
            catch (const char* ch) {
                throw "Invalid Operator";
            }
//If the index of the list is any other operator, the top two value in the stack are popped and stored.
            if (vect[i] == "+") {
                stack.Add(num1 + num2);
//If the index of the list is an addition operator, the two values are added together and added to the stack.
            } else if (vect[i] == "-") {
                stack.Add(num1 - num2);
//If the index of the list is a subtraction operator, the first value is subtracted by the second and added to the stack.
            } else if (vect[i] == "*") {
                stack.Add(num1 * num2);
//If the index of the list is a multiplication operator, the two values are multiplied together and added to the stack.
            } else if (vect[i] == "/") {
                if (num2 == 0) {
                    throw "Cannot divide by zero!";
//If the index of the list is a division operator and the second value is zero, the program throws a divide by zero error.
                } else {
                    stack.Add(num1 / num2);
//Otherwise, the first value is divided by the second value and added to the stack.
                } 
            } else if(vect[i] == "**") {
                stack.Add(pow(num1, num2));
//If the index of the list is the exponentiation operator, the program then muliplies the first value by itself by a power of the second value and adds that to the stack.
            } else if (vect[i] == "%") {
                if (num2 == 0) {
                    throw "Cannot take modulus by zero!";
                } else {
                    stack.Add(fmod(num1, num2));
                }
//If the index of the list is the modulus operator, the first value is modulus'd by the second value and then added to the stack.
            } else {
                throw "Invalid Arithmetic Error!";
            }
        }
    }
    return stack.Pop();
//After the for-loop is finished, the last value in the stack is returned to main.
}