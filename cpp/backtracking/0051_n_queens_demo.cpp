#include <iostream>
#include <vector>
using namespace std;

#define numberofqueens 8
int columnOfQueens[numberofqueens];
// int ch;
class Solution {
    bool isValid(int column, int row)  // here k is the column we have to check
    {
        cout << "Inside isValid for column:" << column << " and row: " << row << endl;
        // cin >> ch;
        for (int c = 0; c < row; c++) {
            int absvalue = abs(columnOfQueens[c] - column);
            if (columnOfQueens[c] == column)  // now only checking if the same column
            {
                cout << "Returning false for column check" << endl;

                return false;
            }
            if (abs(c - row) == absvalue)  // checking the diagonals
            {
                cout << "Returning false for diagonal check" << endl;

                return false;
            }
        }

        /*Now to check the diagoonal*/

        cout << "Returning true" << endl;
        return true;
    }

  public:
    void nQueens(int j, int queens) {
        if (j == queens) {  // base case
            cout << "The columns of queens is " << endl;
            for (int x = 0; x < numberofqueens; x++) {
                cout << columnOfQueens[x] << " ";
            }
            cout << endl;
            // int ch;
            // cin >> ch;
            return;
        }
        for (int i = 0; i < queens; i++)  // we are traversing the columns
        {
            if (isValid(i, j)) {
                cout << ":::::::::)Placing the queen :" << j << " at column " << i
                     << " and row: " << j << endl;
                // cin >> ch;
                columnOfQueens[j] = i;  // for the jth queen, we place it at
                nQueens(j + 1, queens);
                columnOfQueens[j] = INT32_MIN;
            }
        }
    }
};

int main() {

    Solution sol;
    for (int i = 0; i < numberofqueens; i++)
        columnOfQueens[i] = INT32_MIN;
    sol.nQueens(0, numberofqueens);
}