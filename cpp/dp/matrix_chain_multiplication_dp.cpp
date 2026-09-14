#include <bits/stdc++.h>
using namespace std;
int matrixChainOrder(const vector<int>& dims) {

    int n = dims.size();
    if (n < 3)
        return 0;
    // Create a 2D DP array to store the minimum
    // multiplication costs
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Fill the DP array.
    // Here, len is the chain length
    for (int len = 2; len < n; len++)  // length gives the lenght of the chain
    {

        /*We go from the smalles chain to the largest chain */
        for (int i = 0; i < n - len; i++) {
            int j = i + len;
            dp[i][j] = INT_MAX;

            for (int k = i + 1; k < j; k++) {
                cout << "The indices are i: " << i << ", k: " << k << ", j:" << j << endl;
                int cost = dp[i][k] + dp[k][j] + dims.at(i) * dims.at(k) * dims.at(j);

                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    // The minimum cost is stored in dp[0][n-1]
    return dp[0][n - 1];
}

int main() {
    ios::sync_with_stdio(false);

    struct Test {
        vector<int> dims;
        int expected;
        string note;
    };

    vector<Test> tests = {
        // {{}, 0, "empty input"},
        // {{5}, 0, "no matrix (1 dim)"},
        // {{10, 20}, 0, "single matrix -> no multiplication"},
        // {{10, 20, 30}, 6000, "two matrices, only one order"},
        // {{1, 2, 3, 4}, 18, "((AB)C) wins"},
        // {{2, 3, 4, 5}, 64, "small chain"},
        // {{1, 2, 3, 4, 5}, 38, "increasing dims"},
        {{40, 20, 30, 10, 30}, 26000, "classic GfG case"},
        // {{10, 20, 30, 40, 30}, 30000, "classic GfG case"},
        // {{30, 35, 15, 5, 10, 20, 25}, 15125, "CLRS textbook case"},
        // {{1, 1, 1, 1, 1, 1}, 4, "all-ones, cost = n-1"},
    };

    int passed = 0;
    for (size_t i = 0; i < tests.size(); ++i) {
        // calls = 0;
        int got = matrixChainOrder(tests[i].dims);
        bool ok = (got == tests[i].expected);
        passed += ok;
        cout << (ok ? "PASS" : "FAIL") << " #" << i << "  expected=" << tests[i].expected
             << "  got=" << got << "   (" << tests[i].note << ")\n";
    }
    cout << "\n" << passed << "/" << tests.size() << " passed\n";
    return 0;
}