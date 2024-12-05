//Evaluator
#include <iostream>
#include <string>
#include <stack.cpp>
#include <vector>

using namespace std;

double conv_str_doub(const string &x) {
    switch(x) {
        case "0": return 0;
        case "1": return 1;
        case "2": return 2;
        case "3": return 3;
        case "4": return 4;
        case "5": return 5;
        case "6": return 6;
        case "7": return 7;
        case "8": return 8;
        case "9": return 9;
        default: return 111;
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

            switch (vect[i]) {
                case "+":
                    stack.Add(num1 + num2);
                    break;
                case "-":
                    stack.Add(num1 - num2);
                    break;
                case "*":
                    stack.Add(num1 * num2);
                    break;
                case "/":
                    if (num2 == 0) {
                        throw "Cannot divide by zero!";
                    } else {
                        stack.Add(num1 / num2);
                    }
                    break;
            }
        }
    }
    return stack.Pop(); 
}