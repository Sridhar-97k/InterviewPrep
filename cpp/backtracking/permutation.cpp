#include <iostream>
using namespace std;
class Solution {

    char* result;
    int* selected;

  public:
    void permutationSolver(string s) {
        result = new char[s.length()]();
        selected = new int[s.length()]();
        permutation(0, s);
    }

    void permutation(int k, string s) {

        if (k == s.length()) {
            cout << "The result array is :" << endl;
            for (int i = 0; i < s.length(); i++) {
                cout << result[i];
            }
            cout << endl;
        }

        for (int i = 0; i < s.length(); i++)

        {
            // cout << "Here" << endl;
            if (selected[i] == 0) {

                result[k] = s[i];
                selected[i] = 1;
                permutation(k + 1, s);
                selected[i] = 0;
            }
        }
    }
};

int main() {
    Solution sol;
    string permutationString = "abcd";
    sol.permutationSolver(permutationString);
    return 0;
}