//Evaluator
#include <iostream>
#include <string>
#include <stack.cpp>
#include <vector>

using namespace std;

double conv_str_doub(const string &x) {
    if (x == "0") {
        return 0;
    } else if ( x == "1") {
        return 1;
    } else if ( x == "2") {
        return 2;
    } else if ( x == "3") {
        return 3;
    } else if ( x == "4") {
        return 4;
    } else if ( x == "5") {
        return 5;
    } else if ( x == "6") {
        return 6;
    } else if ( x == "7") {
        return 7;
    } else if ( x == "8") {
        return 8;
    } else if ( x == "9") {
        return 9;
    } else {
        return 111;
    }
// This function will read a character and return that digit if that character is a digit. Otherwise, it will return 111 as an error state.
};

double evaluator(vector<string> &vect) {
    Stack<double> stack;

    for (int i = 0; i < vect.size(); i++) {
        if (conv_str_doub(vect[i]) != 111) {
            stack.Add(conv_str_doub(vect[i]));
        } else if(vect[i] == "**") {
            double num = stack.Pop();
            double num2 = stack.Pop();
            for (num2; num2 > 0; num2--) {
                num *= num;
            }
            stack.Add(num);
        } 
        else if(vect[i] == "%") {
            int num1 = stack.Pop();
            int num2 = stack.Pop();
            stack.Add(num1 % num2);
        } else {
            double num1 = stack.Pop();
            double num2 = stack.Pop();

            if (vect[i] == "+") {
                stack.Add(num1 + num2);
                break;
            } else if (vect[i] == "-") {
                stack.Add(num1 - num2);
                break;
            } else if (vect[i] == "*") {
                stack.Add(num1 * num2);
                break;
            } else if (vect[i] == "/") {
                if (num2 == 0) {
                    throw "Cannot divide by zero!";
                } else {
                    stack.Add(num1 - num2);
                }
                break;
            }
        }
    }
    return stack.Pop(); 
}