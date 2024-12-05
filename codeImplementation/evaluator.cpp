//Evaluator
#include <iostream>
//#include <iomanip>
#include <string>
#include "stack.cpp"
#include <vector>
#include <cmath>

using namespace std;

double conv_float(const string& str) {
    
    double result;
    const char *curr_number = str.c_str();
    const char *dec_point_loc = str.c_str();
    const char *first_int = str.c_str();
    int loop_num = 0;
    int converted_num;
    
    if (str[0] == '-' || str[0] == '+') {
        first_int++;
    }
    
    while (*dec_point_loc != '\0') {
        if (*dec_point_loc == '.') {
            break;
        } else {
            dec_point_loc++;
        }
    }
    curr_number = dec_point_loc;
    
    while (curr_number != first_int) {
        curr_number--;
        if (*curr_number >= '0' && *curr_number <= '9'){
            converted_num = *curr_number - '0';
            result += converted_num * pow(10, loop_num);
            loop_num++;
        } else {
            return -999999.99;
        }    
    }
    curr_number = dec_point_loc;
    curr_number++;
    loop_num = 1;
    
    while (*curr_number != '\0'){
        if (*curr_number >= '0' && *curr_number <= '9'){
            converted_num = *curr_number - '0';
            result += converted_num / pow(10, loop_num);
            loop_num++;
            curr_number++;
        } else {
            return -999999.99;
        }
    }
    if (str[0] == '-') {
        return result * -1;
    }
    return result;
}

double evaluator(vector<string> &vect) {
    Stack<double> stack;

    for (int i = 0; i < vect.size(); i++) {
        if (conv_float(vect[i]) != -999999.99) {
            stack.Add(conv_float(vect[i]));
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