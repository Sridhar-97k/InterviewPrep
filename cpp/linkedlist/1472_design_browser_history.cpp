/*
LeetCode 1472 — Design Browser History
URL: https://leetcode.com/problems/design-browser-history/
Difficulty: Medium

Problem:
Design a one-tab browser history. It starts at `homepage`.
- visit(url): navigate to url and clear all forward history.
- back(steps): move backward by at most steps pages and return the current URL.
- forward(steps): move forward by at most steps pages and return the current URL.

Source constraints:
- 1 <= homepage.length <= 20
- 1 <= url.length <= 20
- 1 <= steps <= 100
- homepage and url consist of '.' or lowercase English letters.
- At most 5000 calls will be made to visit, back, and forward.

Target: O(1) amortized time per operation / O(n) space

Compile/run:
g++ -std=c++17 -O2 -Wall -o sol 1472_design_browser_history.cpp && ./sol
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

// ===== YOUR SOLUTION =====
class DoublyLinkedList {

    struct Node {
        string urlData;
        struct Node *prev, *next;
        Node(string val) : urlData(val), prev(nullptr), next(nullptr) {};
    };

  public:
    Node *head = new Node(""), *tail = new Node(""), *currentNode;
    int count = 0;
    string getCurrentVal() {
        return currentNode->urlData;
    }
    void traverseBack(int steps) {

        int i = 0;
        while (currentNode->prev != head && (i < steps) ) {
            currentNode = currentNode->prev;
            i++;
        }
    }
    void traverseForward(int steps) {

        int i = 0;
        while (currentNode->next!= tail && (i < steps) ) {
            currentNode = currentNode->next;
            i++;
        }
    }
    void appendNewNodeBeforeTail(string valToAppend) {
        Node* insertNode = new Node(valToAppend);
        insertNode->prev = tail->prev;
        insertNode->next = tail;
        tail->prev->next = insertNode;
        tail->prev = insertNode;
        currentNode = insertNode;
        count++;
    }
    void updateCount() {
        int i = 0;
        for (auto trav = head->next; trav != tail; trav = trav->next)
            i++;
        count = i;
    }
    void visit(string toVisit) {
        Node* insertNode = new Node(toVisit);
        currentNode->next = insertNode;
        insertNode->prev = currentNode;
        insertNode->next = tail;
        tail->prev = insertNode;
        currentNode = insertNode;
       
    }
    DoublyLinkedList() {}
    DoublyLinkedList(string val) {
        head->next = tail;
        tail->prev = head;
        appendNewNodeBeforeTail(val);
    };
};
class BrowserHistory {
    DoublyLinkedList list;

  public:
    BrowserHistory(string homepage) {
        list = DoublyLinkedList(homepage);
    }

    void visit(string url) {
        list.visit(url);
    }

    string back(int steps) {
        list.traverseBack(steps);

        return list.getCurrentVal();
    }

    string forward(int steps) {

        list.traverseForward(steps);

        return list.getCurrentVal();
    }
};

// ===== TEST INFRA =====

static constexpr long long TIME_LIMIT_US = 200000;

enum class OpType { VISIT, BACK, FORWARD };

struct Operation {
    OpType type;
    string url;
    int steps = 0;

    static Operation Visit(string url) {
        Operation op;
        op.type = OpType::VISIT;
        op.url = std::move(url);
        return op;
    }

    static Operation Back(int steps) {
        Operation op;
        op.type = OpType::BACK;
        op.steps = steps;
        return op;
    }

    static Operation Forward(int steps) {
        Operation op;
        op.type = OpType::FORWARD;
        op.steps = steps;
        return op;
    }
};

struct TestCase {
    string name;
    string homepage;
    vector<Operation> ops;
    vector<string> expected;  // "null" for void operations
};

static string opToString(const Operation& op) {
    if (op.type == OpType::VISIT) {
        return "visit(\"" + op.url + "\")";
    }
    if (op.type == OpType::BACK) {
        return "back(" + to_string(op.steps) + ")";
    }
    return "forward(" + to_string(op.steps) + ")";
}

static string inputToString(const TestCase& tc) {
    ostringstream oss;
    oss << "homepage=\"" << tc.homepage << "\", ops=[";
    for (size_t i = 0; i < tc.ops.size(); ++i) {
        if (i)
            oss << ", ";
        oss << opToString(tc.ops[i]);
    }
    oss << "]";
    return oss.str();
}

static string vecToString(const vector<string>& values) {
    ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i)
            oss << ", ";
        if (values[i] == "null") {
            oss << "null";
        } else {
            oss << '"' << values[i] << '"';
        }
    }
    oss << "]";
    return oss.str();
}

static string truncateText(const string& s, size_t limit = 200) {
    if (s.size() <= limit)
        return s;
    return s.substr(0, limit - 3) + "...";
}

static vector<string> runUser(const TestCase& tc) {
    BrowserHistory browser(tc.homepage);
    vector<string> output;
    output.reserve(tc.ops.size());

    for (const auto& op : tc.ops) {
        if (op.type == OpType::VISIT) {
            browser.visit(op.url);
            output.push_back("null");
        } else if (op.type == OpType::BACK) {
            output.push_back(browser.back(op.steps));
        } else {
            output.push_back(browser.forward(op.steps));
        }
    }

    return output;
}

static size_t inputSize(const TestCase& tc) {
    return tc.ops.size();
}

// ===== TEST DATA =====

static string makeUrl(int id) {
    // Lowercase letters and dots only; <= 20 chars.
    string s = "site";
    int x = id;
    do {
        s.push_back(char('a' + (x % 26)));
        x /= 26;
    } while (x > 0);
    s += ".com";
    return s;
}

static TestCase makeCase(string name, string homepage, vector<Operation> ops) {
    return TestCase{std::move(name), std::move(homepage), std::move(ops), {}};
}

static vector<TestCase> buildBaseTests() {
    vector<TestCase> tests;

    // 1) Official example, verbatim.
    {
        TestCase tc{"official example 1",
                    "leetcode.com",
                    {Operation::Visit("google.com"), Operation::Visit("facebook.com"),
                     Operation::Visit("youtube.com"), Operation::Back(1), Operation::Back(1),
                     Operation::Forward(1), Operation::Visit("linkedin.com"), Operation::Forward(2),
                     Operation::Back(2), Operation::Back(7)},
                    {"null", "null", "null", "facebook.com", "google.com", "facebook.com", "null",
                     "linkedin.com", "google.com", "leetcode.com"}};
        tests.push_back(std::move(tc));
    }

    // Handwritten edge and behavior cases.
    tests.push_back(makeCase("single back at homepage", "a.com", {Operation::Back(1)}));

    tests.push_back(makeCase("single forward at homepage", "a.com", {Operation::Forward(1)}));

    tests.push_back(
        makeCase("visit once then back", "a.com", {Operation::Visit("b.com"), Operation::Back(1)}));

    tests.push_back(makeCase("visit once then oversized back", "a.com",
                             {Operation::Visit("b.com"), Operation::Back(100)}));

    tests.push_back(makeCase("back then forward", "a.com",
                             {Operation::Visit("b.com"), Operation::Visit("c.com"),
                              Operation::Back(1), Operation::Forward(1)}));

    tests.push_back(makeCase("oversized forward", "a.com",
                             {Operation::Visit("b.com"), Operation::Visit("c.com"),
                              Operation::Back(2), Operation::Forward(100)}));

    tests.push_back(
        makeCase("visit clears one forward page", "a.com",
                 {Operation::Visit("b.com"), Operation::Visit("c.com"), Operation::Back(1),
                  Operation::Visit("d.com"), Operation::Forward(1)}));

    tests.push_back(
        makeCase("visit clears long forward chain", "a.com",
                 {Operation::Visit("b.com"), Operation::Visit("c.com"), Operation::Visit("d.com"),
                  Operation::Visit("e.com"), Operation::Back(3), Operation::Visit("x.com"),
                  Operation::Forward(100)}));

    tests.push_back(makeCase(
        "repeated back at boundary", "a.com",
        {Operation::Visit("b.com"), Operation::Back(1), Operation::Back(1), Operation::Back(100)}));

    tests.push_back(
        makeCase("repeated forward at boundary", "a.com",
                 {Operation::Visit("b.com"), Operation::Visit("c.com"), Operation::Back(2),
                  Operation::Forward(1), Operation::Forward(1), Operation::Forward(100)}));

    tests.push_back(
        makeCase("alternating back forward", "a.com",
                 {Operation::Visit("b.com"), Operation::Visit("c.com"), Operation::Visit("d.com"),
                  Operation::Back(1), Operation::Forward(1), Operation::Back(1),
                  Operation::Forward(1), Operation::Back(2), Operation::Forward(1)}));

    tests.push_back(makeCase("duplicate urls are separate visits", "a.com",
                             {Operation::Visit("b.com"), Operation::Visit("b.com"),
                              Operation::Back(1), Operation::Forward(1)}));

    tests.push_back(makeCase("visit homepage again", "a.com",
                             {Operation::Visit("b.com"), Operation::Visit("a.com"),
                              Operation::Back(1), Operation::Back(1), Operation::Forward(2)}));

    tests.push_back(makeCase(
        "minimum length urls", "a",
        {Operation::Visit("b"), Operation::Visit("."), Operation::Back(1), Operation::Forward(1)}));

    tests.push_back(makeCase("maximum length urls", "aaaaaaaaaaaaaaaaaaaa",
                             {Operation::Visit("bbbbbbbbbbbbbbbbbbbb"),
                              Operation::Visit("cccccccccccccccccccc"), Operation::Back(1),
                              Operation::Forward(1)}));

    tests.push_back(makeCase("dots in urls", "a.b.c",
                             {Operation::Visit("x.y.z"), Operation::Visit("..a.."),
                              Operation::Back(1), Operation::Forward(1)}));

    tests.push_back(
        makeCase("step one chain", "root.com",
                 {Operation::Visit("a.com"), Operation::Visit("b.com"), Operation::Visit("c.com"),
                  Operation::Back(1), Operation::Back(1), Operation::Back(1), Operation::Forward(1),
                  Operation::Forward(1), Operation::Forward(1)}));

    tests.push_back(
        makeCase("step hundred exact saturation", "root.com",
                 {Operation::Visit("a.com"), Operation::Visit("b.com"), Operation::Visit("c.com"),
                  Operation::Back(100), Operation::Forward(100)}));

    tests.push_back(
        makeCase("multiple branch replacements", "root.com",
                 {Operation::Visit("a.com"), Operation::Visit("b.com"), Operation::Visit("c.com"),
                  Operation::Back(2), Operation::Visit("x.com"), Operation::Visit("y.com"),
                  Operation::Back(1), Operation::Visit("z.com"), Operation::Forward(100),
                  Operation::Back(100)}));

    return tests;
}

// ===== REFERENCE (SPOILER — naive only) =====

#ifndef USE_REFERENCE
#define USE_REFERENCE 1
#endif

#if USE_REFERENCE

class NaiveBrowserHistory {
  public:
    explicit NaiveBrowserHistory(string homepage) : pages_{std::move(homepage)}, current_(0) {}

    void visit(const string& url) {
        // Intentionally naive: physically erase every forward entry.
        while (pages_.size() > current_ + 1) {
            pages_.erase(pages_.begin() + static_cast<long long>(current_ + 1));
        }
        pages_.push_back(url);
        ++current_;
    }

    string back(int steps) {
        // Intentionally naive: move one step at a time.
        while (steps > 0 && current_ > 0) {
            --current_;
            --steps;
        }
        return pages_[current_];
    }

    string forward(int steps) {
        // Intentionally naive: move one step at a time.
        while (steps > 0 && current_ + 1 < pages_.size()) {
            ++current_;
            --steps;
        }
        return pages_[current_];
    }

  private:
    vector<string> pages_;
    size_t current_;
};

static vector<string> runReference(const TestCase& tc) {
    NaiveBrowserHistory browser(tc.homepage);
    vector<string> output;
    output.reserve(tc.ops.size());

    for (const auto& op : tc.ops) {
        if (op.type == OpType::VISIT) {
            browser.visit(op.url);
            output.push_back("null");
        } else if (op.type == OpType::BACK) {
            output.push_back(browser.back(op.steps));
        } else {
            output.push_back(browser.forward(op.steps));
        }
    }

    return output;
}

static void fillExpected(vector<TestCase>& tests) {
    for (auto& tc : tests) {
        if (tc.expected.empty()) {
            tc.expected = runReference(tc);
        }
    }
}

static void appendGeneratedTests(vector<TestCase>& tests) {
    mt19937 rng(42);

    // Cases 21..85: small-to-medium randomized operation streams.
    for (int caseNo = 21; caseNo <= 85; ++caseNo) {
        int opCount = 8 + (caseNo - 21) * 3;
        vector<Operation> ops;
        ops.reserve(opCount);

        for (int j = 0; j < opCount; ++j) {
            int pick = static_cast<int>(rng() % 100);
            if (pick < 48) {
                ops.push_back(Operation::Visit(makeUrl(caseNo * 1000 + j)));
            } else if (pick < 74) {
                ops.push_back(Operation::Back(1 + static_cast<int>(rng() % 100)));
            } else {
                ops.push_back(Operation::Forward(1 + static_cast<int>(rng() % 100)));
            }
        }

        tests.push_back(
            makeCase("generated mixed " + to_string(caseNo), makeUrl(caseNo), std::move(ops)));
    }

    // Cases 86..94: medium/large stress streams.
    for (int caseNo = 86; caseNo <= 94; ++caseNo) {
        int opCount = 500 + (caseNo - 86) * 250;
        vector<Operation> ops;
        ops.reserve(opCount);

        for (int j = 0; j < opCount; ++j) {
            int pick = static_cast<int>(rng() % 100);
            if (pick < 55) {
                ops.push_back(Operation::Visit(makeUrl(caseNo * 10000 + j)));
            } else if (pick < 78) {
                ops.push_back(Operation::Back(1 + static_cast<int>(rng() % 100)));
            } else {
                ops.push_back(Operation::Forward(1 + static_cast<int>(rng() % 100)));
            }
        }

        tests.push_back(
            makeCase("generated stress " + to_string(caseNo), makeUrl(caseNo), std::move(ops)));
    }

    // 95: long pure visit chain.
    {
        vector<Operation> ops;
        for (int i = 0; i < 3000; ++i) {
            ops.push_back(Operation::Visit(makeUrl(950000 + i)));
        }
        tests.push_back(makeCase("large pure visit chain", "home.com", std::move(ops)));
    }

    // 96: long chain then repeated large back/forward jumps.
    {
        vector<Operation> ops;
        for (int i = 0; i < 2000; ++i) {
            ops.push_back(Operation::Visit(makeUrl(960000 + i)));
        }
        for (int i = 0; i < 1000; ++i) {
            ops.push_back((i % 2 == 0) ? Operation::Back(100) : Operation::Forward(100));
        }
        tests.push_back(makeCase("large navigation oscillation", "home.com", std::move(ops)));
    }

    // 97: repeatedly clear a substantial forward history.
    {
        vector<Operation> ops;
        for (int block = 0; block < 400; ++block) {
            for (int j = 0; j < 6; ++j) {
                ops.push_back(Operation::Visit(makeUrl(970000 + block * 10 + j)));
            }
            ops.push_back(Operation::Back(5));
            ops.push_back(Operation::Visit(makeUrl(979000 + block)));
        }
        tests.push_back(makeCase("repeated forward history clearing", "home.com", std::move(ops)));
    }

    // 98: boundary-heavy navigation.
    {
        vector<Operation> ops;
        for (int i = 0; i < 1000; ++i) {
            ops.push_back(Operation::Visit(makeUrl(980000 + i)));
        }
        for (int i = 0; i < 2000; ++i) {
            ops.push_back((i % 2 == 0) ? Operation::Back(100) : Operation::Forward(100));
        }
        ops.push_back(Operation::Back(100));
        ops.push_back(Operation::Back(100));
        ops.push_back(Operation::Forward(100));
        tests.push_back(makeCase("boundary heavy large case", "home.com", std::move(ops)));
    }

    // 99: maximum 5000 calls, deterministic mixed operations.
    {
        vector<Operation> ops;
        ops.reserve(5000);
        for (int i = 0; i < 5000; ++i) {
            int pick = static_cast<int>(rng() % 100);
            if (pick < 50) {
                ops.push_back(Operation::Visit(makeUrl(990000 + i)));
            } else if (pick < 75) {
                ops.push_back(Operation::Back(1 + static_cast<int>(rng() % 100)));
            } else {
                ops.push_back(Operation::Forward(1 + static_cast<int>(rng() % 100)));
            }
        }
        tests.push_back(makeCase("maximum 5000 calls mixed", "home.com", std::move(ops)));
    }

    // 100: maximum 5000 calls with branch-heavy behavior.
    {
        vector<Operation> ops;
        ops.reserve(5000);
        for (int i = 0; i < 1000; ++i) {
            ops.push_back(Operation::Visit(makeUrl(1000000 + i)));
        }
        for (int i = 0; i < 1000; ++i) {
            ops.push_back(Operation::Back(1 + (i % 100)));
            ops.push_back(Operation::Visit(makeUrl(1010000 + i)));
            ops.push_back(Operation::Forward(1 + (i % 100)));
            ops.push_back(Operation::Visit(makeUrl(1020000 + i)));
        }
        tests.push_back(makeCase("maximum 5000 calls branch heavy", "home.com", std::move(ops)));
    }
}

#else

static void fillExpected(vector<TestCase>&) {}
static void appendGeneratedTests(vector<TestCase>&) {}

#endif

int main() {
    vector<TestCase> tests = buildBaseTests();

#if USE_REFERENCE
    appendGeneratedTests(tests);
    fillExpected(tests);
#else
    cerr << "USE_REFERENCE must be enabled to build generated expected outputs.\n";
    return 1;
#endif

    if (tests.size() != 100) {
        cerr << "Harness error: expected exactly 100 test cases, got " << tests.size() << ".\n";
        return 1;
    }

    int passed = 0;
    long long totalUs = 0;
    long long slowestUs = -1;
    int slowestIndex = -1;
    string slowestName;
    bool anyOverLimit = false;

    for (size_t i = 0; i < tests.size(); ++i) {
        const auto start = chrono::steady_clock::now();
        vector<string> actual = runUser(tests[i]);
        const auto end = chrono::steady_clock::now();

        const long long elapsedUs =
            chrono::duration_cast<chrono::microseconds>(end - start).count();

        totalUs += elapsedUs;
        if (elapsedUs > slowestUs) {
            slowestUs = elapsedUs;
            slowestIndex = static_cast<int>(i);
            slowestName = tests[i].name;
        }
        if (elapsedUs > TIME_LIMIT_US) {
            anyOverLimit = true;
        }

        const bool ok = (actual == tests[i].expected);
        if (ok)
            ++passed;

        cout << setw(3) << (i + 1) << " | " << tests[i].name << " | " << (ok ? "PASS" : "FAIL")
             << " | " << elapsedUs << " us"
             << " | input size " << inputSize(tests[i]) << '\n';

        if (!ok) {
            cout << "    input:    " << truncateText(inputToString(tests[i])) << '\n';
            cout << "    expected: " << truncateText(vecToString(tests[i].expected)) << '\n';
            cout << "    actual:   " << truncateText(vecToString(actual)) << '\n';
        }
    }

    const double averageUs = tests.empty() ? 0.0 : static_cast<double>(totalUs) / tests.size();

    cout << "\n===== SUMMARY =====\n";
    cout << "passed: " << passed << "/100\n";
    cout << "total time: " << totalUs << " us\n";
    cout << fixed << setprecision(2) << "average time: " << averageUs << " us\n";
    cout << "slowest case: " << (slowestIndex + 1) << " | " << slowestName << " | " << slowestUs
         << " us\n";

    if (anyOverLimit) {
        cout << "WARNING: at least one case exceeded TIME_LIMIT_US = " << TIME_LIMIT_US << " us\n";
    }

    return passed == 100 ? 0 : 1;
}
