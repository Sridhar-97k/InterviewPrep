#include <bits/stdc++.h>
using namespace std;

static long long calls = 0;
int M[100][100];
int m(int i, int j, const vector<int> &dims)
{

    if (i + 1 == j)
    {

        M[i][j] == 0;
        return 0;
    }
    if (M[i][j] != -1) // suposse for a call, we have calcualted, then we can refer it from the table
        return M[i][j];
    //  if they are -1, then we assign INT_MAX to them
    M[i][j] = INT_MAX;
    int cost = 0;
    for (int k = i + 1; k < j; k++)
    {
        M[i][k] = m(i, k, dims);
        M[k][j] = m(k, j, dims);
        cost = M[i][k] + M[k][j] + dims.at(i) * dims.at(j) * dims.at(k);
        if (cost < M[i][j])
            M[i][j] = cost;
    }
    return M[i][j];
}

int matrixChainOrder(const vector<int> &dims)
{
    if (dims.size() < 2)
        return 0;
    for (int c = 0; c < dims.size(); c++)
    {
        for (int d = 0; d < dims.size(); d++)
            M[c][d] = -1;
    }
    return m(0, (int)dims.size() - 1, dims);
}

int main()
{
    ios::sync_with_stdio(false);

    struct Test
    {
        vector<int> dims;
        int expected;
        string note;
    };

    vector<Test> tests = {
        {{}, 0, "empty input"},
        {{5}, 0, "no matrix (1 dim)"},
        {{10, 20}, 0, "single matrix -> no multiplication"},
        {{10, 20, 30}, 6000, "two matrices, only one order"},
        {{1, 2, 3, 4}, 18, "((AB)C) wins"},
        {{2, 3, 4, 5}, 64, "small chain"},
        {{1, 2, 3, 4, 5}, 38, "increasing dims"},
        {{40, 20, 30, 10, 30}, 26000, "classic GfG case"},
        {{10, 20, 30, 40, 30}, 30000, "classic GfG case"},
        {{30, 35, 15, 5, 10, 20, 25}, 15125, "CLRS textbook case"},
        {{1, 1, 1, 1, 1, 1}, 4, "all-ones, cost = n-1"},
    };

    int passed = 0;
    for (size_t i = 0; i < tests.size(); ++i)
    {
        calls = 0;
        int got = matrixChainOrder(tests[i].dims);
        bool ok = (got == tests[i].expected);
        passed += ok;
        cout << (ok ? "PASS" : "FAIL") << " #" << i
             << "  expected=" << tests[i].expected
             << "  got=" << got
             << "  calls=" << calls
             << "   (" << tests[i].note << ")\n";
    }
    cout << "\n"
         << passed << "/" << tests.size() << " passed\n";
    return 0;
}