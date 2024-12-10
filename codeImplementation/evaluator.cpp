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
//This namespace removes the need to use the std:: namespace
double conv_float(const string& str) {
//This function converts a string value into a float
    double result;
    const char *curr_number = str.c_str();
    const char *dec_point_loc = str.c_str();
    const char *first_int = str.c_str();
    int loop_num = 0;
    int converted_num;
//These variables will be utilized throughout the function
    if (str[0] == '-' || str[0] == '+') {
        first_int++;
    }
//If there is a unary operator in the first index, the first_int object is incremented by one
    while (*dec_point_loc != '\0') {
        if (*dec_point_loc == '.') {
            break;
        } else {
            dec_point_loc++;
        }
    }
    curr_number = dec_point_loc;
//If there is a decimal point located in the string, the dec_point_loc object will locate it and assign it to curr_number.    
    while (curr_number != first_int) {
        curr_number--;
        if (*curr_number >= '0' && *curr_number <= '9'){
            converted_num = *curr_number - '0';
            result += converted_num * pow(10, loop_num);
            loop_num++;
//This code checks the digits left of the decimal and correctly attains the value to the left of the decimal by multiplying powers of ten.
        } else {
            return -999999.99;
//If the statement is invalid, -999999.99 is returned
        }    
    }
    curr_number = dec_point_loc;
    curr_number++;
    loop_num = 1;
//This relocates the decimal and sets curr_number to that location
    while (*curr_number != '\0'){
        if (*curr_number >= '0' && *curr_number <= '9'){
            converted_num = *curr_number - '0';
            result += converted_num / pow(10, loop_num);
            loop_num++;
            curr_number++;
//This code checks the digits right of the decimal and correctly attains the value to the left of the decimal by dividing powers of ten.
        } else {
            return -999999.99;
//If the string is invalid, -999999.99 is returned
        }
    }
    if (str[0] == '-') {
        return result * -1;
    }
//If there is a negative in the first index of the string, the result is multiplied by -1
    return result;
//If the string is a valid entry, result is returned
}

double evaluator(vector<string> &vect) {
    Stack<double> stack = Stack<double>();
//The stack object will be used to evaluate the expression in postorder
    for (int i = 0; i < (int)vect.size(); i++) {
        //This for-loop goes through each value of the vector/list from parser
        if (extractNumber(vect[i]) != -999999.99) {
            stack.Add(extractNumber(vect[i]));
            //If the index of the list is a numeric value, it is added to stack
        }
        else {
            // The order  of these is reversed; don't question it.
            double num2 = stack.Pop();
            double num1 = stack.Pop();
            //If the index of the list is any other operator, the top two value in the stack are popped and stored.
            if (vect[i] == "+") {
                stack.Add(num1 + num2);
                //If the index of the list is an addition operator, the two values are added together and added to the stack.
            }
            else if (vect[i] == "-") {
                stack.Add(num1 - num2);
                //If the index of the list is a subtraction operator, the first value is subtracted by the second and added to the stack.
            }
            else if (vect[i] == "*") {
                stack.Add(num1 * num2);
                //If the index of the list is a multiplication operator, the two values are multiplied together and added to the stack.
            }
            else if (vect[i] == "/") {
                if (num2 == 0) {
                    throw "Cannot divide by zero!";
                    //If the index of the list is a division operator and the second value is zero, the program throws a divide by zero error.
                }
                else {
                    stack.Add(num1 / num2);
                    //Otherwise, the first value is divided by the second value and added to the stack.
                }
            }
            else if (vect[i] == "**") {
                stack.Add(pow(num1, num2));
                //If the index of the list is the exponentiation operator, the program then muliplies the first value by itself by a power of the second value and adds that to the stack.
            }
            else if (vect[i] == "%") {
                stack.Add(fmod(num1, num2));
                //If the index of the list is the modulus operator, the first value is modulus'd by the second value and then added to the stack.
            }
        }
    }
    //After the for-loop is finished, the last value in the stack is returned to main.
    return stack.Pop(); 
}