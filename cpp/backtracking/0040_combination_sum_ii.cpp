/*
LeetCode 40 — Combination Sum II
URL: https://leetcode.com/problems/combination-sum-ii/
Difficulty: Medium

Problem:
Given a collection of candidate numbers and a target, return all unique
combinations whose sum is target. Each input element may be used at most once.
The result must not contain duplicate combinations.

Source constraints:
- 1 <= candidates.length <= 100
- 1 <= candidates[i] <= 50
- 1 <= target <= 30

Target: exponential/output-sensitive time; O(n) auxiliary recursion space
excluding the returned output.

Compile/run:
g++ -std=c++17 -O2 -Wall -o sol 0040_combination_sum_ii.cpp && ./sol
*/

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

static constexpr long long TIME_LIMIT_US = 200000;

// ===== YOUR SOLUTION =====
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        // TODO: implement
        return {};
    }
};

// ===== TEST INFRA =====
struct TestCase {
    string name;
    vector<int> candidates;
    int target;
    vector<vector<int>> expected;
};


static string truncStr(const string& s, size_t limit = 200) {
    if (s.size() <= limit) return s;
    return s.substr(0, limit - 3) + "...";
}

static string vecToString(const vector<int>& v) {
    ostringstream out;
    out << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) out << ",";
        out << v[i];
    }
    out << "]";
    return out.str();
}

static string combosToString(const vector<vector<int>>& vv) {
    ostringstream out;
    out << "[";
    for (size_t i = 0; i < vv.size(); ++i) {
        if (i) out << ",";
        out << vecToString(vv[i]);
    }
    out << "]";
    return out.str();
}

static vector<vector<int>> normalize(vector<vector<int>> v) {
    for (auto& row : v) sort(row.begin(), row.end());
    sort(v.begin(), v.end());
    return v;
}


static bool validate(const TestCase& tc, const vector<vector<int>>& actual) {
    return normalize(actual) == normalize(tc.expected);
}

static string inputToString(const TestCase& tc) {
    ostringstream out;
    out << "candidates=" << vecToString(tc.candidates)
        << ", target=" << tc.target;
    return out.str();
}

// ===== REFERENCE (SPOILER — naive only) =====
#define USE_REFERENCE 1

#if USE_REFERENCE
static void refEnumerateFrequencies(
    const vector<pair<int, int>>& freq,
    int idx,
    int remaining,
    vector<int>& current,
    vector<vector<int>>& out
) {
    if (remaining == 0) {
        out.push_back(current);
        return;
    }
    if (idx == static_cast<int>(freq.size()) || remaining < 0) return;

    const int value = freq[idx].first;
    const int available = freq[idx].second;
    const int maxCount = min(available, remaining / value);

    // Naive frequency-vector enumeration: choose how many copies of each
    // distinct value to use, then advance to the next distinct value.
    for (int count = 0; count <= maxCount; ++count) {
        for (int k = 0; k < count; ++k) current.push_back(value);
        refEnumerateFrequencies(
            freq,
            idx + 1,
            remaining - count * value,
            current,
            out
        );
        for (int k = 0; k < count; ++k) current.pop_back();
    }
}

static vector<vector<int>> referenceCombinationSum2(
    vector<int> candidates,
    int target
) {
    sort(candidates.begin(), candidates.end());

    vector<pair<int, int>> freq;
    for (int x : candidates) {
        if (freq.empty() || freq.back().first != x) {
            freq.push_back({x, 1});
        } else {
            ++freq.back().second;
        }
    }

    vector<vector<int>> out;
    vector<int> current;
    refEnumerateFrequencies(freq, 0, target, current, out);
    return normalize(out);
}
#endif

// ===== TEST DATA =====
static void addReferenceCase(
    vector<TestCase>& tests,
    string name,
    vector<int> candidates,
    int target
) {
#if USE_REFERENCE
    tests.push_back({
        move(name),
        candidates,
        target,
        referenceCombinationSum2(candidates, target)
    });
#else
    tests.push_back({move(name), move(candidates), target, {}});
#endif
}

static vector<TestCase> buildTests() {
    vector<TestCase> tests;
    tests.reserve(100);

    // Official examples, verbatim.
    tests.push_back({
        "official_example_1",
        {10, 1, 2, 7, 6, 1, 5},
        8,
        {{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}}
    });
    tests.push_back({
        "official_example_2",
        {2, 5, 2, 1, 2},
        5,
        {{1, 2, 2}, {5}}
    });

    // Handwritten edge/behavior cases.
    addReferenceCase(tests, "single_exact", {5}, 5);
    addReferenceCase(tests, "single_miss", {5}, 4);
    addReferenceCase(tests, "two_equal_needed", {1, 1}, 2);
    addReferenceCase(tests, "two_equal_not_reusable", {2, 2}, 6);
    addReferenceCase(tests, "all_equal_many", {1,1,1,1,1}, 3);
    addReferenceCase(tests, "duplicate_branch_pressure", {1,1,1,2,2,2,5}, 5);
    addReferenceCase(tests, "all_above_target", {6,6,7,8}, 5);
    addReferenceCase(tests, "exact_candidate_duplicate", {7,7,7}, 7);
    addReferenceCase(tests, "unordered_duplicates", {4,1,3,1,2,4,2}, 6);
    addReferenceCase(tests, "target_one", {1,1,2,3}, 1);
    addReferenceCase(tests, "target_max_30", {1,2,2,3,5,8,13,21,21}, 30);
    addReferenceCase(tests, "candidate_max_50", {50,30,20,10}, 30);
    addReferenceCase(tests, "many_ones_limit_100", vector<int>(100, 1), 30);

    vector<int> hundredHigh;
    for (int i = 0; i < 100; ++i) hundredHigh.push_back(20 + (i % 31));
    addReferenceCase(tests, "length_100_high_values", hundredHigh, 30);

    vector<int> repeatedFive;
    for (int i = 0; i < 20; ++i) {
        repeatedFive.push_back(1);
        repeatedFive.push_back(2);
        repeatedFive.push_back(3);
        repeatedFive.push_back(4);
        repeatedFive.push_back(5);
    }
    addReferenceCase(tests, "length_100_dense_duplicates", repeatedFive, 12);

    addReferenceCase(tests, "many_duplicate_groups",
                     {1,1,2,2,3,3,4,4,5,5,6,6}, 10);
    addReferenceCase(tests, "no_solution_parity", {2,2,4,4,6,6}, 7);
    addReferenceCase(tests, "one_of_each_chain", {1,2,4,8,16}, 30);

    mt19937 rng(42);

    while (tests.size() < 100) {
        const size_t idx = tests.size();
        int n;
        int valueMax;
        int target;

        if (idx < 45) {
            n = 1 + static_cast<int>(rng() % 8);
            valueMax = 10;
            target = 1 + static_cast<int>(rng() % 15);
        } else if (idx < 85) {
            n = 8 + static_cast<int>(rng() % 13);
            valueMax = 20;
            target = 8 + static_cast<int>(rng() % 23);
        } else {
            n = 40 + static_cast<int>(rng() % 61);
            valueMax = 50;
            target = 15 + static_cast<int>(rng() % 16);
        }

        vector<int> candidates;
        candidates.reserve(n);

        for (int i = 0; i < n; ++i) {
            int value;
            if (idx >= 85) {
                // Large tests emphasize legal length limits without making
                // the naive reference explode.
                value = 15 + static_cast<int>(rng() % 36);
            } else {
                value = 1 + static_cast<int>(rng() % valueMax);
            }
            candidates.push_back(value);
        }

        ostringstream name;
        if (idx < 45) name << "generated_small_";
        else if (idx < 85) name << "generated_medium_";
        else name << "generated_large_";
        name << setw(2) << setfill('0') << idx;

        addReferenceCase(tests, name.str(), candidates, target);
    }

    return tests;
}

// ===== MAIN =====
int main() {
    vector<TestCase> tests = buildTests();

    if (tests.size() != 100) {
        cerr << "Harness error: expected exactly 100 tests, got "
             << tests.size() << "\n";
        return 2;
    }

    int passed = 0;
    long long totalUs = 0;
    long long slowestUs = -1;
    int slowestIndex = -1;
    bool exceededLimit = false;

    cout << "index | name | PASS/FAIL | elapsed | input size\n";

    for (size_t i = 0; i < tests.size(); ++i) {
        const TestCase& tc = tests[i];
        vector<int> candidates = tc.candidates;

        Solution sol;
        const auto start = chrono::steady_clock::now();
        vector<vector<int>> actual = sol.combinationSum2(candidates, tc.target);
        const auto end = chrono::steady_clock::now();

        const long long elapsedUs =
            chrono::duration_cast<chrono::microseconds>(end - start).count();

        const bool ok = validate(tc, actual);
        passed += ok ? 1 : 0;
        totalUs += elapsedUs;

        if (elapsedUs > slowestUs) {
            slowestUs = elapsedUs;
            slowestIndex = static_cast<int>(i);
        }
        if (elapsedUs > TIME_LIMIT_US) exceededLimit = true;

        cout << (i + 1) << " | " << tc.name << " | "
             << (ok ? "PASS" : "FAIL") << " | "
             << elapsedUs << " us | " << tc.candidates.size() << "\n";

        if (!ok) {
            cout << "  input:    " << truncStr(inputToString(tc)) << "\n";
            cout << "  expected: "
                 << truncStr(combosToString(normalize(tc.expected))) << "\n";
            cout << "  actual:   "
                 << truncStr(combosToString(normalize(actual))) << "\n";
        }
    }

    const double avgUs = static_cast<double>(totalUs) / tests.size();

    cout << "\nSummary\n";
    cout << "passed: " << passed << "/100\n";
    cout << "total time: " << totalUs << " us\n";
    cout << fixed << setprecision(2)
         << "average time: " << avgUs << " us\n";

    if (slowestIndex >= 0) {
        cout << "slowest case: " << (slowestIndex + 1)
             << "/" << tests[slowestIndex].name
             << "/" << slowestUs << " us\n";
    }

    if (exceededLimit) {
        cout << "WARNING: at least one case exceeded TIME_LIMIT_US="
             << TIME_LIMIT_US << "\n";
    }

    return passed == 100 ? 0 : 1;
}
