// =====================================================================================
// 146. LRU Cache
// https://leetcode.com/problems/lru-cache/
// Difficulty: Medium
//
// PROBLEM (restated)
//   Design a data structure obeying the constraints of a Least Recently Used (LRU)
//   cache. Implement the class `LRUCache`:
//     - LRUCache(int capacity)      : initialize the cache with positive size capacity.
//     - int  get(int key)           : return the value stored for key, or -1 if absent.
//     - void put(int key, int value): if key is present, update its value; otherwise
//                                     insert the key-value pair. If the insertion makes
//                                     the number of stored keys exceed capacity, evict
//                                     the least recently used key.
//   Both get and put must run in O(1) average time.
//   Note: both a successful `get` and a `put` on an existing key count as a use of that
//   key for recency purposes.
//
// CONSTRAINTS (as given by the source)
//   1 <= capacity <= 3000
//   0 <= key <= 10^4
//   0 <= value <= 10^5
//   At most 2 * 10^5 calls will be made to get and put.
//
// Target: O(1) average time per operation / O(capacity) space
//
// HOW CORRECTNESS IS CHECKED
//   Each test case is a (capacity, operation sequence) pair. The harness replays the
//   sequence against a fresh LRUCache and records one result per operation: the return
//   value for get, and the sentinel `null` for put. The recorded vector is compared for
//   exact equality against the expected vector; on mismatch the index of the first
//   differing operation is reported. Answers are unique, so no validate() predicate is
//   needed and no floating point is involved.
//
//   Expected values for the generated cases (21-100) are produced at start-up by the
//   reference at the bottom of this file. That takes a couple of seconds because of the
//   two largest cases; set -DUSE_REFERENCE=0 to skip it (those cases then report SKIP).
//
//   With the empty stub this prints 99 FAIL and 1 PASS: case 3 (get_on_empty_cache)
//   expects nothing but -1, which the stub returns by default.
//
// COMPILE + RUN
//   g++ -std=c++17 -O2 -Wall -o sol 0146_lru_cache.cpp && ./sol
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;

// See "REFERENCE" at the bottom of the file. Override with -DUSE_REFERENCE=0.
#ifndef USE_REFERENCE
#define USE_REFERENCE 1
#endif

static const long long TIME_LIMIT_US = 500000;  // per-case warning threshold
static const int NA = INT_MIN;                  // "null": the (void) result of a put

// One recorded operation. type 0 = put(key, val), type 1 = get(key).
struct Op {
    int type;
    int key;
    int val;
};
static inline Op P(int k, int v) {
    Op o;
    o.type = 0;
    o.key = k;
    o.val = v;
    return o;
}
static inline Op G(int k) {
    Op o;
    o.type = 1;
    o.key = k;
    o.val = 0;
    return o;
}

// =========================== YOUR SOLUTION ===========================
// Exact LeetCode signature. This is the only part of the file you edit.
class MyList {
    struct ListNode {
        int val;
        struct ListNode *next, *prev;

        ListNode() : val(0), next(nullptr), prev(nullptr) {}
        ListNode(int x) : val(x), next(nullptr), prev(nullptr) {};
    };
    unordered_map<int, ListNode*> listNodeMap;
    ListNode* head = new ListNode(0);
    ListNode* tail = new ListNode(0);
    int count;

  public:
    MyList() : count(0) {
        head->next = tail;
        tail->prev = head;
    }
    void insertBefore(ListNode* newNode, ListNode* node) {

        newNode->prev = node->prev;
        newNode->next = node;
        node->prev->next = newNode;
        node->prev = newNode;
    }
    ListNode* unlink(ListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        return node;
    }
    void appendToFirst(int val) {
        ListNode* newNode = new ListNode(val);
        listNodeMap[val] = newNode;
        insertBefore(newNode, head->next);
    }
    void updateRecency(int key) {
        ListNode* node = listNodeMap.at(key);
        unlink(node);
        insertBefore(node, head->next);
    }
    int evictLast() {
        ListNode* evict = unlink(tail->prev);
        int return_val = evict->val;
        listNodeMap.erase(return_val);
        delete evict;
        return return_val;
    }
};
class LRUCache {

  public:
    MyList list;
    map<int, int> cache;
    int cap;
    int count;
    LRUCache(int capacity) : count(0):{
        // TODO: implement
        cap = capacity;
        
    }

    int get(int key) {
        // complete
        if (cache.find(key) != cache.end()) {
            int returnval = cache[key];
            list.updateRecency(key);
            return returnval;
        } else
            return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            cache[key] = value;

        } else {
            if (count == cap) {
                int evict = list.evictLast();
                cache.erase(evict);
                cache[key] = value;
                list.appendToFirst(key);

            } else {
                cache[key] = value;
                list.appendToFirst(key);
                count++;
            }
        }
        list.updateRecency(key);
    }
};

// ============================ TEST INFRA ============================

struct TestCase {
    string name;
    int capacity = 1;
    vector<Op> ops;
    vector<int> expected;
    bool hasExpected = false;
};

static TestCase makeCase(const string& name, int cap, vector<Op> ops, vector<int> expected) {
    TestCase tc;
    tc.name = name;
    tc.capacity = cap;
    tc.ops = move(ops);
    tc.expected = move(expected);
    tc.hasExpected = true;
    return tc;
}

// Adapter: test data -> the solution's interface -> a comparable vector<int>.
static vector<int> runSolution(const TestCase& tc) {
    LRUCache cache(tc.capacity);
    vector<int> out;
    out.reserve(tc.ops.size());
    for (size_t i = 0; i < tc.ops.size(); ++i) {
        const Op& op = tc.ops[i];
        if (op.type == 1) {
            out.push_back(cache.get(op.key));
        } else {
            cache.put(op.key, op.val);
            out.push_back(NA);
        }
    }
    return out;
}

static string clip(const string& s, size_t n = 200) {
    if (s.size() <= n)
        return s;
    return s.substr(0, n) + "... [" + to_string(s.size()) + " chars total]";
}

static string opsToString(const TestCase& tc) {
    string s = "capacity=" + to_string(tc.capacity) + " ops=[";
    for (size_t i = 0; i < tc.ops.size(); ++i) {
        if (i)
            s += ",";
        if (tc.ops[i].type == 1) {
            s += "get(" + to_string(tc.ops[i].key) + ")";
        } else {
            s += "put(" + to_string(tc.ops[i].key) + "," + to_string(tc.ops[i].val) + ")";
        }
        if (s.size() > 600) {
            s += ",...";
            break;
        }
    }
    s += "] (" + to_string(tc.ops.size()) + " ops)";
    return s;
}

static string resToString(const vector<int>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i)
            s += ",";
        s += (v[i] == NA) ? "null" : to_string(v[i]);
        if (s.size() > 600) {
            s += ",...";
            break;
        }
    }
    s += "]";
    return s;
}

// Exact comparison; returns index of first difference, or -1 if identical.
static long long firstDiff(const vector<int>& a, const vector<int>& b) {
    size_t n = min(a.size(), b.size());
    for (size_t i = 0; i < n; ++i) {
        if (a[i] != b[i])
            return (long long)i;
    }
    if (a.size() != b.size())
        return (long long)n;
    return -1;
}

// ============================ TEST DATA =============================

#if USE_REFERENCE
static vector<int> referenceRun(int capacity, const vector<Op>& ops);  // defined below
#endif

static inline int rint(mt19937& rng, int lo, int hi) {
    return lo + (int)(rng() % (uint32_t)(hi - lo + 1));
}

struct GenSpec {
    int nOps;
    int capacity;
    int keyLo;
    int keyHi;
    int getPct;
};

static TestCase genCase(const string& name, const GenSpec& s, mt19937& rng) {
    TestCase tc;
    tc.name = name;
    tc.capacity = s.capacity;
    tc.hasExpected = false;
    tc.ops.reserve(s.nOps);
    for (int i = 0; i < s.nOps; ++i) {
        int k = rint(rng, s.keyLo, s.keyHi);
        if ((int)(rng() % 100u) < s.getPct)
            tc.ops.push_back(G(k));
        else
            tc.ops.push_back(P(k, rint(rng, 0, 100000)));
    }
    return tc;
}

static vector<TestCase> buildTests() {
    vector<TestCase> t;

    // ---- 1: example from the problem statement, verbatim ----
    t.push_back(makeCase("example_1", 2,
                         {P(1, 1), P(2, 2), G(1), P(3, 3), G(2), P(4, 4), G(1), G(3), G(4)},
                         {NA, NA, 1, NA, -1, NA, -1, 3, 4}));

    // ---- 2-20: hand-written edge cases ----

    // minimum capacity
    t.push_back(
        makeCase("cap1_basic_evict", 1, {P(1, 1), G(1), P(2, 2), G(1), G(2)}, {NA, 1, NA, -1, 2}));

    // reads before any write (note: passes trivially with the empty stub)
    t.push_back(makeCase("get_on_empty_cache", 2, {G(0), G(10000), G(1)}, {-1, -1, -1}));

    // overwriting a key must not create a second entry
    t.push_back(makeCase("overwrite_then_evict", 2,
                         {P(1, 1), P(1, 2), G(1), P(2, 2), P(3, 3), G(1), G(2), G(3)},
                         {NA, NA, 2, NA, NA, -1, 2, 3}));

    // a put on an existing key counts as a use
    t.push_back(makeCase("put_existing_refreshes_recency", 2,
                         {P(1, 1), P(2, 2), P(1, 10), P(3, 3), G(2), G(1), G(3)},
                         {NA, NA, NA, NA, -1, 10, 3}));

    // a successful get counts as a use
    t.push_back(makeCase("get_refreshes_recency", 2,
                         {P(1, 1), P(2, 2), G(1), P(3, 3), G(2), G(1), G(3)},
                         {NA, NA, 1, NA, -1, 1, 3}));

    // key 0 and value 0 must be distinguishable from "absent"
    t.push_back(makeCase("zero_key_zero_value", 2, {P(0, 0), G(0), P(1, 0), G(1), G(0)},
                         {NA, 0, NA, 0, 0}));

    // constraint ceilings for key and value
    t.push_back(makeCase("max_key_max_value", 2,
                         {P(10000, 100000), G(10000), P(0, 0), G(0), G(10000)},
                         {NA, 100000, NA, 0, 100000}));

    // exactly fills capacity, nothing may be evicted
    t.push_back(
        makeCase("fill_to_capacity_no_evict", 5,
                 {P(1, 2), P(2, 4), P(3, 6), P(4, 8), P(5, 10), G(1), G(2), G(3), G(4), G(5)},
                 {NA, NA, NA, NA, NA, 2, 4, 6, 8, 10}));

    // reinserting an evicted key evicts someone else
    t.push_back(makeCase("evict_then_reinsert", 2,
                         {P(1, 1), P(2, 2), P(3, 3), G(1), P(1, 10), G(2), G(3), G(1)},
                         {NA, NA, NA, -1, NA, -1, 3, 10}));

    // a hot key survives regardless of age of insertion
    t.push_back(makeCase("repeated_gets_protect_key", 2,
                         {P(1, 1), P(2, 2), G(1), G(1), G(1), P(3, 3), G(2), G(1), G(3)},
                         {NA, NA, 1, 1, 1, NA, -1, 1, 3}));

    // repeated puts of one key into a size-1 cache
    t.push_back(makeCase("same_key_repeated_puts_cap1", 1,
                         {P(7, 1), P(7, 2), P(7, 3), G(7), P(8, 8), G(7), G(8)},
                         {NA, NA, NA, 3, NA, -1, 8}));

    // many more distinct keys than capacity: only the last 3 survive
    {
        vector<Op> ops;
        vector<int> exp;
        for (int i = 1; i <= 10; ++i) {
            ops.push_back(P(i, i));
            exp.push_back(NA);
        }
        ops.push_back(G(7));
        exp.push_back(-1);
        ops.push_back(G(8));
        exp.push_back(8);
        ops.push_back(G(9));
        exp.push_back(9);
        ops.push_back(G(10));
        exp.push_back(10);
        ops.push_back(G(1));
        exp.push_back(-1);
        t.push_back(makeCase("many_distinct_keys_small_cap", 3, ops, exp));
    }

    // a missing get must not disturb recency
    t.push_back(makeCase("interleaved_miss_then_hit", 2,
                         {G(1), P(1, 1), G(2), P(2, 2), G(3), P(3, 3), G(1), G(2), G(3)},
                         {-1, NA, -1, NA, -1, NA, -1, 2, 3}));

    // capacity far exceeds the number of distinct keys: no eviction ever
    {
        vector<Op> ops;
        vector<int> exp;
        for (int i = 0; i < 50; ++i) {
            ops.push_back(P(i, i + 1));
            exp.push_back(NA);
        }
        for (int i = 0; i < 50; ++i) {
            ops.push_back(G(i));
            exp.push_back(i + 1);
        }
        t.push_back(makeCase("capacity_far_exceeds_keys", 3000, ops, exp));
    }

    // longer crafted recency sequence
    t.push_back(
        makeCase("mixed_recency_sequence", 3,
                 {P(1, 1), P(2, 2), P(3, 3), G(1), P(4, 4), G(2), G(3), P(5, 5), G(1), G(4), G(5)},
                 {NA, NA, NA, 1, NA, -1, 3, NA, -1, 4, 5}));

    // value update keeps the key alive across an eviction
    t.push_back(makeCase("update_value_keeps_key_alive", 3,
                         {P(1, 1), P(2, 2), P(3, 3), P(1, 11), P(4, 4), G(2), G(1), G(3), G(4)},
                         {NA, NA, NA, NA, NA, -1, 11, 3, 4}));

    // all misses, then all hits
    t.push_back(makeCase(
        "all_miss_then_all_hit", 4,
        {G(1), G(2), G(3), G(4), P(1, 1), P(2, 2), P(3, 3), P(4, 4), G(1), G(2), G(3), G(4)},
        {-1, -1, -1, -1, NA, NA, NA, NA, 1, 2, 3, 4}));

    // worst-case thrashing: every new key evicts the previous one
    t.push_back(
        makeCase("thrashing_cycle", 2,
                 {P(1, 1), P(2, 2), P(3, 3), G(1), P(4, 4), G(2), P(5, 5), G(3), G(4), G(5)},
                 {NA, NA, NA, -1, NA, -1, NA, -1, 4, 5}));

    // maximum capacity, filled exactly, then one eviction
    {
        vector<Op> ops;
        vector<int> exp;
        for (int i = 0; i < 3000; ++i) {
            ops.push_back(P(i, i * 10));
            exp.push_back(NA);
        }
        ops.push_back(G(0));
        exp.push_back(0);  // key 0 becomes most recent
        ops.push_back(P(3000, 30000));
        exp.push_back(NA);  // evicts key 1
        ops.push_back(G(1));
        exp.push_back(-1);
        ops.push_back(G(0));
        exp.push_back(0);
        ops.push_back(G(3000));
        exp.push_back(30000);
        ops.push_back(G(2999));
        exp.push_back(29990);
        t.push_back(makeCase("max_capacity_boundary_evict", 3000, ops, exp));
    }

    // ---- 21-100: deterministic generated cases, ramping in size ----
    mt19937 rng(42);
    struct Group {
        const char* prefix;
        int count;
        int opLo, opHi;
        int capLo, capHi;
        int keyLo, keyHi;
    };
    const Group groups[] = {
        {"rand_small", 40, 1, 400, 1, 32, 0, 40},
        {"rand_medium", 20, 1000, 6000, 8, 256, 0, 512},
        {"rand_large", 12, 20000, 40000, 64, 1024, 0, 4096},
        {"rand_xl", 6, 50000, 80000, 256, 1024, 0, 10000},
    };
    for (const Group& g : groups) {
        for (int i = 0; i < g.count; ++i) {
            GenSpec s;
            s.nOps = rint(rng, g.opLo, g.opHi);
            s.capacity = rint(rng, g.capLo, g.capHi);
            s.keyLo = g.keyLo;
            s.keyHi = g.keyHi;
            s.getPct = rint(rng, 30, 70);
            char buf[64];
            snprintf(buf, sizeof(buf), "%s_%02d", g.prefix, i + 1);
            t.push_back(genCase(buf, s, rng));
        }
    }
    // at the constraint ceiling: 2*10^5 calls
    {
        GenSpec s;
        s.nOps = 200000;
        s.capacity = 3000;
        s.keyLo = 0;
        s.keyHi = 10000;
        s.getPct = 50;
        t.push_back(genCase("ceiling_maxops_maxcap", s, rng));
    }
    {
        GenSpec s;
        s.nOps = 200000;
        s.capacity = 512;
        s.keyLo = 0;
        s.keyHi = 1000;
        s.getPct = 60;
        t.push_back(genCase("ceiling_maxops_hot_keys", s, rng));
    }

#if USE_REFERENCE
    for (size_t i = 0; i < t.size(); ++i) {
        if (!t[i].hasExpected) {
            t[i].expected = referenceRun(t[i].capacity, t[i].ops);
            t[i].hasExpected = true;
        }
    }
#endif

    return t;
}

// ================ REFERENCE (SPOILER -- naive only) =================
// Do not read this if you have not solved the problem yet. It is an intentionally
// slow O(capacity) per operation simulation used only to compute expected outputs
// for the generated cases. Compile with -DUSE_REFERENCE=0 to leave it out.

#if USE_REFERENCE
namespace ref_naive {

struct NaiveCache {
    int cap;
    vector<pair<int, int>> v;  // v.front() is the least recently used entry

    explicit NaiveCache(int c) : cap(c) {}

    int indexOf(int key) const {
        for (int i = 0; i < (int)v.size(); ++i) {
            if (v[i].first == key)
                return i;
        }
        return -1;
    }

    int get(int key) {
        int i = indexOf(key);
        if (i < 0)
            return -1;
        pair<int, int> e = v[i];
        v.erase(v.begin() + i);
        v.push_back(e);
        return e.second;
    }

    void put(int key, int value) {
        int i = indexOf(key);
        if (i >= 0)
            v.erase(v.begin() + i);
        else if ((int)v.size() >= cap)
            v.erase(v.begin());
        v.push_back(make_pair(key, value));
    }
};

}  // namespace ref_naive

static vector<int> referenceRun(int capacity, const vector<Op>& ops) {
    ref_naive::NaiveCache c(capacity);
    vector<int> out;
    out.reserve(ops.size());
    for (size_t i = 0; i < ops.size(); ++i) {
        const Op& op = ops[i];
        if (op.type == 1) {
            out.push_back(c.get(op.key));
        } else {
            c.put(op.key, op.val);
            out.push_back(NA);
        }
    }
    return out;
}
#endif

// ================================ MAIN ==============================

int main() {
#if USE_REFERENCE
    fprintf(stderr, "computing expected values for generated cases...\n");
#endif
    auto buildStart = chrono::steady_clock::now();
    vector<TestCase> tests = buildTests();
    auto buildEnd = chrono::steady_clock::now();
    long long buildUs = chrono::duration_cast<chrono::microseconds>(buildEnd - buildStart).count();

    const int total = (int)tests.size();
    int passed = 0, failed = 0, skipped = 0, overLimit = 0;
    long long totalUs = 0, slowestUs = -1;
    int slowestIdx = -1;

    printf("LeetCode 146 -- LRU Cache -- %d cases (setup %lld us)\n", total, buildUs);
    printf("%-5s  %-28s  %-6s  %12s  %10s\n", "#", "name", "status", "time(us)", "ops");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < total; ++i) {
        const TestCase& tc = tests[i];

        if (!tc.hasExpected) {
            ++skipped;
            printf("%-5d  %-28s  %-6s  %12s  %10zu\n", i + 1, tc.name.c_str(), "SKIP", "-",
                   tc.ops.size());
            continue;
        }

        auto t0 = chrono::steady_clock::now();
        vector<int> actual = runSolution(tc);
        auto t1 = chrono::steady_clock::now();
        long long us = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();

        totalUs += us;
        if (us > slowestUs) {
            slowestUs = us;
            slowestIdx = i;
        }
        if (us > TIME_LIMIT_US)
            ++overLimit;

        long long d = firstDiff(actual, tc.expected);
        bool ok = (d < 0);
        if (ok)
            ++passed;
        else
            ++failed;

        printf("%-5d  %-28s  %-6s  %12lld  %10zu\n", i + 1, tc.name.c_str(), ok ? "PASS" : "FAIL",
               us, tc.ops.size());

        if (!ok) {
            printf("       input    : %s\n", clip(opsToString(tc)).c_str());
            printf("       expected : %s\n", clip(resToString(tc.expected)).c_str());
            printf("       actual   : %s\n", clip(resToString(actual)).c_str());
            printf("       first mismatch at op %lld", d);
            if (d < (long long)tc.ops.size()) {
                const Op& op = tc.ops[(size_t)d];
                if (op.type == 1)
                    printf(" -> get(%d)", op.key);
                else
                    printf(" -> put(%d,%d)", op.key, op.val);
            }
            printf("\n");
        }
    }

    printf("--------------------------------------------------------------------------\n");
    printf("passed   : %d/%d   failed: %d   skipped: %d\n", passed, total, failed, skipped);
    printf("time     : total %lld us", totalUs);
    int run = passed + failed;
    if (run > 0)
        printf("   average %lld us", totalUs / run);
    printf("\n");
    if (slowestIdx >= 0) {
        printf("slowest  : #%d %s  %lld us\n", slowestIdx + 1, tests[slowestIdx].name.c_str(),
               slowestUs);
    }
    if (overLimit > 0) {
        printf("WARNING  : %d case(s) exceeded TIME_LIMIT_US = %lld\n", overLimit, TIME_LIMIT_US);
    }
    if (skipped > 0) {
        printf("NOTE     : %d case(s) skipped (reference disabled)\n", skipped);
    }

    return (failed == 0 && skipped == 0) ? 0 : 1;
}