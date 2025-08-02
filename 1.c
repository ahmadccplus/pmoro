#include <iostream>
#include <string.h>
#include <stack>

using namespace std;

// Function to return precedence of operators
int prec(char c)
{
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string infixToPostfix(string s)
{
    stack<char> st; // For stack operations, we are using C++ built-in stack
    string result;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        // If the scanned character is an operand, add it to output string.
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
            result += c;
            cout << "result = " << result << endl;
        }
        // If the scanned character is an '(', push it to the stack.
        else if (c == '(') {
            st.push('(');
            cout << "pushing left bracket" << endl;
        }
        // If the scanned character is an ')',
        // pop and to output string from the stack until an '(' is encountered.
        else if (c == ')') {
            cout<< "reaching right bracket" << endl;
            while ((!st.empty()) && (st.top() != '(')) {
                result += st.top();
                cout << "popping: " << st.top() << endl;
                cout << "result = " << result << endl;
                st.pop();
            }
            cout << "popping left bracket" << endl;
            st.pop();
        }
        // If an operator is scanned
        else if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^')) {
            while ((!st.empty()) && (st.top() != '(')
                   && prec(s[i]) <= prec(st.top())) {
                result += st.top();
                cout << "popping: " << st.top() << endl;
                cout << "result = " << result << endl;
                st.pop();
            }
            st.push(c);
            cout << "pushing: " << st.top() << endl;
        }
    }

    // Pop all the remaining elements from the stack
    while (!st.empty()) {
        result += st.top();
        cout << "result = " << result << endl;
        cout << "popping: " << st.top() << endl;
        st.pop();
    }

    cout << result << endl;
    return result;
}


int main()
{
    string exp = "((A+B)*C-D)*E";
    // string exp = "a+b*(c^d-e)^(f+g*h)-i"; // Output: abcd^e-fgh*+^*+i-

    string res = infixToPostfix(exp);
    return 0;
}
