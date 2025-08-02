#include<iostream>
#include<string.h>
#include<stack>
using namespace std;

// Function to return precedence of operators
int prec(char c)
{
    if(c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string infixToPrefix(string s)
{
    stack<char> st;
    string result;

    // Scan the infix notation in reverse order
    for(int i = s.length()-1; i >= 0; i--)
    {
        char c = s[i];

        // If character is an operand, then add to the result string.
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c >= '0' && c <= '9'){
            result += c;
            cout << "result = " << result << endl;
        }
        // If the character is a closing parenthesis, then push it to the stack.
        else if (c == ')'){
            st.push(')');
            cout << "pushing a right bracket" << endl;
        }
        // If the character is an opening parenthesis, pop the elements in the stack till we find
        // the closing parenthesis that corresponds. Add the popped elements to the result string
        // except for the parenthesis.
        else if (c == '('){
            cout << "reaching a left bracket" << endl;
            while (!st.empty() && st.top() != ')'){
                result += st.top();
                cout << "popping: " << st.top() << endl;
                cout << "result = " << result << endl;
                st.pop();
            }
            cout << "Popping a right bracket" << endl;
            st.pop();
        }
        // If a character scanned is operator.
        else if ((c == '+') || (c == '-') || (c == '/') || (c == '*') || (c == '^')){
            // Case 3: If the operator has less precedence than the top of the stack, pop the operator
            // and output it to the output of the prefix notation, then check the above condition with
            // the new top of the stack again.
            while (!st.empty() && st.top() != ')' && prec(s[i]) < prec(st.top())){
                result += st.top();
                cout << "popping: " << st.top() << endl;
                cout << "result = " << result << endl;
                st.pop();
            }

            // Case 1: If the stack top is a closing parenthesis, push the operator to the stack.
            // Case 2: If the operator has greater or equal precedence than the top of the stack,
            // push the operator to the stack.
            st.push(c);
            cout << "pushing: " << st.top() << endl;
        }
    }

    while (!st.empty()){
        result += st.top();
        cout << "popping: " << st.top() << endl;
        cout << "result = " << result << endl;
        st.pop();
    }

    // After scanning all the characters, reverse the result string to get the prefix notation.
    for(int i = 0; i < result.length(); i++){
        st.push(result[i]);
    }

    result = "";
    for(int i = 0; i < result.length(); i++){
        result += st.top();
        st.pop();
    }

    cout << "result = " << result << endl;
    return result;
}

int main()
{
    //string exp = "((P+Q)*R)/(S-T))";
    //string exp = "2+3*1-5";
    string exp = "(2+3)*1-5";
    string res = infixToPrefix(exp);
    return 0;
}
