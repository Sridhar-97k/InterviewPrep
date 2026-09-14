#include <bits/stdc++.h>
using namespace std;

static long long calls = 0;

int m(int i, int j, const vector<int> &dims)
{
    calls++;
    if (i + 1 == j)
        return 0;

    int min_cost = INT32_MAX;
    for (int k = i + 1; k < j; k++)
    {
        int cost = m(i, k, dims) + m(k, j, dims) + dims.at(i) * dims.at(k) * dims.at(j);
        if (cost < min_cost)
            min_cost = cost;
    }
    return min_cost;
}

int matrixChainOrder(const vector<int> &dims)
{
    if (dims.size() < 2)
        return 0;
    return m(0, dims.size() - 1, dims);
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