#include <iostream> 
#include <string>   
#include "stack.cpp" 
#include <vector>
using namespace std;

// Function to return precedence of operators
int prec(const string& op) {
    if (op == "**") return 3;
    else if (op == "*" || op == "/" || op == "%") return 2;
    else if (op == "+" || op == "-") return 1;
    else return 0;
}

// The main function to convert infix expression
// to postfix expression
vector<string> parse(string s) {
    
    // Initialize both the stack what will help with precedence and the
    // result, which is the postfix expression we are trying to build.
    Stack<string> st;
    vector<string> result;

    // To create this postfix expression we need to loop through the valid string that was given
    // as a parameter and handle adding the operators and operands in correct order.
    for (int i = 0; i < (int)s.length(); i++) {
        char c = s[i];
        
        // If the scanned character is a digit, find the whole number and add it to the result.
        if (c >= '0' && c <= '9'){
            string current_num = string(); // Creates an empty string that will hold the new number till we add it to the vector
            
            // To properly grab each operand from the infix string we will need to loop through
            // the part of the string that holds the operand.
            // We need to loop because operands can be bigger than one integer.
            
            // We can simply loop till the next empty space as the string should have already be checked for validity
            // by the lexer
            
            // This loop checks if I is greater than the size of the list to ensure we do not
            // cause a memory error. It also checks if the next current character is a space 
            // because the format of the string should be one space between all operators and
            // operands.
            while (i < (int)s.size() && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) {
                current_num += s[i];
                i++;
            }
            i--; //i is decremented to point to the last digit so that the next index is correct.
            // Then of course add this operand to the resulting postfix expression
            result.push_back(current_num);
        }
        // If the scanned character is a ' '(empty space), just continue past this iteration.
        else if (c == ' ') {
            continue;
        }
        // If the scanned character is an '(', push it to the stack.
        else if (c == '(') {
            // This pushes a string version because everything is beind handled as string literals.
            // We are treating everything as string literals because of the operator "**" being longer
            // than a char.
            st.Add("(");
        }
        // This else if handles the scenario if the parsed char is a operator.
        else if (c == '*' || c == '/' || c == '%' || c == '+' || c == '-') {
            
            // Since the calculator has to handle unary operators we need to handle a special case for that.
            // According to our syntax for expressions in our calculator a unary operator is either a "+" or "-"
            // that is directly connect to the number, that is no space between them.
            if ((c == '+' || c == '-') && s[i + 1] >= '0' && s[i + 1] <= '9') {
                string current_num = string();
                current_num += c;
                i++;
                while (i < (int)s.size() && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) {
                    current_num += s[i];
                    i++;
                }
                i--;
                result.push_back(current_num);
                continue;
            }
            // Since the unary can be on the outside of a parentheses like , +( 4 ), we have to handle that case.
            // This is done by determining the sign, since there could be mulitpule signs in a nested parentheses
            // situation. This parse the number and then put that value in out postfix expression.
            else if ((c == '+' || c == '-') && s[i + 1] == '(') {
                
                // Since we are looking for an operand we will need a string to hold its value.
                // We also need to determine the sign so we start by getting its current sign and iterate
                // so the loop doesnt check the same char twice.
                string current_num = string();
                char sign = c;
                i++;
                
                // Then we need to loop through all possible nested parentheses and we can do this by basically just looping till we hit
                // the number itself. This also helps handle the situation where there is an unary connected to the number itself.
                while (i < (int)s.size() && (!(s[i] >= '0' && s[i] <= '9') || s[i] == ' ')) {
                    
                    // This catches the case that our current sign is negative and we ran into another
                    // negative so we need to flip the sign and keep going.
                    if (s[i] == '-' && sign == '-') {
                        sign = '+';
                        i++;
                    }
                    // This covers the case that we ran into a negative and currently our sign is positive, in this
                    // case we need to flip our sign and continue/
                    else if (s[i] == '-' && sign == '+') {
                        sign = '-';
                        i++;
                    }
                    else if (s[i] == '(') {
                        // This pushes a string version because everything is beind handled as string literals.
                        // We are treating everything as string literals because of the operator "**" being longer
                        // than a char.
                        st.Add("(");
                        i++;
                    }
                    // Since there are two other possible combonations of the current operator and sign 
                    // this else catches thoes cases. They can be caught and simply iterated past because
                    // they do not change the sign.
                    else {
                        
                        i++;
                    }
                }
                // Once we have determined the sign of the value we need to acutally determine the value itself.
                // This is done by looping till there is no longer any value. That is the first ')' is found.
                // Again since by the time this function has recived the string it has been lexed to check for validity,
                // So here it is safe to assume the parentheses match.
                current_num += sign;
                while (i < (int)s.size() && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) {
                    current_num += s[i];
                    i++;
                }
                // Then of course we need to add this new value to the postfix expression.
                result.push_back(current_num);
                i--;
                continue;
            }

            // Initialize curr_op
            string curr_op;
            // Since everything is currently in char form we need to convert before we can even check the precedence
            // of the operator we are currently parsing.
            // Also, since we are parsing one operator at a time and have two different operators that start the same,
            // "*" and "**", we need to handle that issue.
            // This if handles that issue by checking the next char in the sting, this resolves the issue because if the
            // next char is '*' we know that out current operator is "**", otherwise we know its the char we just parsed.
            if (s[i] == '*' && s[i + 1] == '*') {
                curr_op = "**";
                i++; // Here we need to iterate i so on the next loop it doesnt grab the second '*'.
            }else {
                // This assigns one copy of the character c as a string to curr_op.
                curr_op += c;
            }
            
            // if the stack is empty then just add the parsed op to the stack.
            if (st.IsEmpty()) {
                st.Add(curr_op);
                continue; // This continue is here so that we dont add operators twice.
            }
            // If the stack is not empty we will need to handle two cases, that the top of the stack has a higher precedence
            // or the parse op has a higher precedence.
            // So we need to initialize these precedence values. 
            int prec_of_op = prec(curr_op);
            int prec_of_top = prec(st.Peek()); 
            
            // If the precedence of the top of the stack is greater than or equal we need to pop off every operator on the 
            // stack till the precedence of the operator is greater. 
            while (prec_of_top >= prec_of_op && !st.IsEmpty()) {
                result.push_back(st.Pop()); // This uses top because top returns the top value of the stack.
                // Then since top doesnt remove it we need to remove said value with pop.
                // This if makes sure the stack is not empty before we try to acceses the top of it so it doesnt cause a 
                // segmentation fault. This error can occur because we pop the remaining item of the stack in the previous
                // line and wouldnt have time for the while conidtion to check yet.
                if (!st.IsEmpty()) {
                    prec_of_top = prec(st.Peek()); // Update the precedence of the top of the stack to compare on next loop.
                }
            }
            // If the precedence of the operator is greater than the top of the stack we add it to the stack.
            st.Add(curr_op);
        }
        // If the scanned character is an ')', remove from the stack till the parentheses are closed.
        else if (c == ')') {
            // This loops till we find the other parentheses that closes the one we just parsed.
            while (st.Peek() != "(") {
                result.push_back(st.Peek());
                st.Pop(); 
            }
            // This handles popping off the last '(', we do this outside of the loop so that not parentheses
            // are added to the expression.
            // It does not need them because how we manipulate the stack should correctly represent this order
            // of operations without the need for the parentheses.
            st.Pop();
        }
    }
    // Since the the above for loop can finish while there are still operators in the stack
    // we need to make sure these operators make it into the final expression.
    // So this loops till we have emptied the stack, we are emptying the stack one operator at
    // a time and adding each one to the end of the new postfix expression.
    while (!st.IsEmpty()) {
        result.push_back(st.Peek()); 
        st.Pop(); 
    }
    // After parsing through the expression and emptying the expression we have the final postfix
    // expression and we can return it so that the postfix expression can be evaluated.
    return result;
}