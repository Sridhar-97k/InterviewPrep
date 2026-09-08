#include <string>
#include <stack>
#include <iostream>
using namespace std;
class Solution {
  public:
    int minAddToMakeValid(string s) {
        stack<char> myStack;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(' && myStack.top() == ')')
                myStack.pop();
            else if (s[i] == '(')
                myStack.push('(');
            else if (s[i] == ')' && (myStack.top() == '('))
                myStack.pop();
            else if (s[i] == ')')
                myStack.push(')');
        }
        return myStack.size();
    }
};

int main() {
    Solution sol;
    string myString = "())";
    cout << sol.minAddToMakeValid(myString) << endl;
}