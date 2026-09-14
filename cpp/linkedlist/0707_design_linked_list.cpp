// ============================================================================
//  LeetCode 707 - Design Linked List
//
//  Write your solution in the marked section. Then just:
//
//      g++ -std=c++17 -g -fsanitize=address,undefined 0707_design_linked_list.cpp -o lc707 && ./lc707
//
//  No flags, no arguments, no other files. All 100 tests are in main().
//
//  Each test is replayed against a std::deque reference model, so you never
//  write expected values yourself. To add your own test, drop one more line
//  into main():
//
//      TEST("my case", { oh(1), ot(2), od(0), og(0) });
//
//  A working solution is in a comment at the bottom. Don't scroll there yet.
// ============================================================================

#include <cstdio>
#include <deque>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// ============================================================================
//  ####  YOUR SOLUTION - THE ONLY PART YOU EDIT  ####
// ============================================================================

class MyLinkedList {
    // Suggested shape (delete this and do it your way):
    //
    //   struct Node { int val; Node *prev, *next; ... };
    //   Node* head;   // sentinel, never holds data
    //   Node* tail;   // sentinel, never holds data
    //   int size;
    //
    //   Node* nodeAt(int index);              // walk from the nearer end
    //   void  insertBefore(Node* pos, int v); // owns size++
    //   void  unlink(Node* node);             // owns size--

    struct ListNode {
        int val;
        ListNode *next, *prev;
        ListNode() : prev(nullptr), next(nullptr) {};
        ListNode(int val) : val(val), prev(nullptr), next(nullptr) {};
        ListNode(int val, ListNode* nextVal) : val(val), next(nextVal) {};
    };

    ListNode *head, *tail;
    int count;

  public:
    MyLinkedList() : count(0) {
        // TODO: allocate both sentinels and wire them to each other
        head = new ListNode();
        tail = new ListNode();
        head->next = tail;
        tail->prev = head;
    }

    ~MyLinkedList() {
        // delete head;
        // delete tail;

        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            delete curr;
            curr = next;
        }
        // TODO: free every node, both sentinels included.
        // The build above has leak detection on, so skipping this shows up
        // as a LeakSanitizer report even when all 100 tests pass.
    }
    void unlink(ListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        count--;
    }
    int get(int index) {

        if (index >= count || index < 0)
            return -1;
        return nodeAt(index)->val;
    }
    ListNode* nodeAt(int index) {
        ListNode* curr = head->next;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr;
    }
    void insertBefore(ListNode* node, int val) {
        ListNode* newNode = new ListNode(val);
        newNode->prev = node->prev;
        newNode->next = node;
        node->prev->next = newNode;
        node->prev = newNode;

        count++;
    }
    void addAtHead(int val) {

        // TODO
        insertBefore(head->next, val);
    }

    void addAtTail(int val) {

        insertBefore(tail, val);
    }

    void addAtIndex(int index, int val) {
        if (index > count || index < 0)
            return;

        if (index == count) {
            insertBefore(tail, val);
        } else {
            insertBefore(nodeAt(index), val);
        }
    }

    void deleteAtIndex(int index) {
        if (index >= count || index < 0)
            return;
        unlink(nodeAt(index));
    }
};

// ============================================================================
//  ####  HARNESS - NOTHING BELOW HERE NEEDS EDITING  ####
// ============================================================================

enum OpKind { ADD_HEAD, ADD_TAIL, ADD_INDEX, DEL_INDEX, GET };

struct Op {
    OpKind kind;
    int a = 0;  // val for addAtHead/addAtTail, index otherwise
    int b = 0;  // val for addAtIndex
};

// shorthand used when writing tests
static Op oh(int v) {
    return {ADD_HEAD, v, 0};
}  // addAtHead(v)
static Op ot(int v) {
    return {ADD_TAIL, v, 0};
}  // addAtTail(v)
static Op oi(int i, int v) {
    return {ADD_INDEX, i, v};
}  // addAtIndex(i, v)
static Op od(int i) {
    return {DEL_INDEX, i, 0};
}  // deleteAtIndex(i)
static Op og(int i) {
    return {GET, i, 0};
}  // get(i)

static std::string render(const Op& op) {
    char buf[64];
    switch (op.kind) {
    case ADD_HEAD:
        std::snprintf(buf, sizeof buf, "addAtHead(%d)", op.a);
        break;
    case ADD_TAIL:
        std::snprintf(buf, sizeof buf, "addAtTail(%d)", op.a);
        break;
    case ADD_INDEX:
        std::snprintf(buf, sizeof buf, "addAtIndex(%d, %d)", op.a, op.b);
        break;
    case DEL_INDEX:
        std::snprintf(buf, sizeof buf, "deleteAtIndex(%d)", op.a);
        break;
    case GET:
        std::snprintf(buf, sizeof buf, "get(%d)", op.a);
        break;
    }
    return buf;
}

// Reference model. Deliberately dumb: a deque with explicit bounds checks.
struct Reference {
    std::deque<int> d;
    int get(int i) const {
        if (i < 0 || i >= (int)d.size())
            return -1;
        return d[i];
    }
    void addAtHead(int v) {
        d.push_front(v);
    }
    void addAtTail(int v) {
        d.push_back(v);
    }
    void addAtIndex(int i, int v) {
        if (i < 0 || i > (int)d.size())
            return;
        d.insert(d.begin() + i, v);
    }
    void deleteAtIndex(int i) {
        if (i < 0 || i >= (int)d.size())
            return;
        d.erase(d.begin() + i);
    }
};

static int g_id = 0, g_passed = 0, g_failed = 0;
static size_t g_ops = 0;

// Runs one test: your list and the reference side by side, comparing every get.
static void TEST(const std::string& name, const std::vector<Op>& ops) {
    int id = ++g_id;
    g_ops += ops.size();

    // stderr, flushed before the test runs, so a segfault still tells you where
    std::cerr << "running test " << id << " [" << name << "]\r" << std::flush;

    MyLinkedList list;
    Reference ref;

    for (size_t i = 0; i < ops.size(); i++) {
        const Op& op = ops[i];
        switch (op.kind) {
        case ADD_HEAD:
            list.addAtHead(op.a);
            ref.addAtHead(op.a);
            break;
        case ADD_TAIL:
            list.addAtTail(op.a);
            ref.addAtTail(op.a);
            break;
        case ADD_INDEX:
            list.addAtIndex(op.a, op.b);
            ref.addAtIndex(op.a, op.b);
            break;
        case DEL_INDEX:
            list.deleteAtIndex(op.a);
            ref.deleteAtIndex(op.a);
            break;
        case GET: {
            int got = list.get(op.a), want = ref.get(op.a);
            if (got != want) {
                std::cerr << std::string(70, ' ') << "\r" << std::flush;
                std::cout << "FAIL  test " << id << "  [" << name << "]\n"
                          << "  op #" << i << ": " << render(op) << "\n"
                          << "  expected " << want << ", got " << got << "\n"
                          << "\n  --- minimal repro (paste into a scratch main) ---\n"
                          << "  MyLinkedList L;\n";
                for (size_t k = 0; k <= i; k++) {
                    std::cout << "  L." << render(ops[k]) << ";";
                    if (k == i)
                        std::cout << "   // <-- FAILS HERE";
                    std::cout << "\n";
                }
                std::cout << "  ------------------------------------------------\n\n";
                g_failed++;
                return;
            }
            break;
        }
        }
    }
    std::cerr << std::string(70, ' ') << "\r" << std::flush;
    g_passed++;
}

// Builds a randomised op sequence. Tracks a model size so indices stay mostly
// in range; sizeBias controls how often they overshoot the end.
static std::vector<Op> randomOps(std::mt19937& rng, int n, int sizeBias, bool allowNegative) {
    auto R = [&](int lo, int hi) { return (int)std::uniform_int_distribution<int>(lo, hi)(rng); };
    std::vector<Op> ops;
    int size = 0;
    for (int i = 0; i < n; i++) {
        int kind = R(0, 4), val = R(0, 1000);
        int idx = (allowNegative && R(0, 99) < 15) ? R(-3, -1) : R(0, size + sizeBias);
        switch (kind) {
        case 0:
            ops.push_back(oh(val));
            size++;
            break;
        case 1:
            ops.push_back(ot(val));
            size++;
            break;
        case 2:
            ops.push_back(oi(idx, val));
            if (idx >= 0 && idx <= size)
                size++;
            break;
        case 3:
            ops.push_back(od(idx));
            if (idx >= 0 && idx < size)
                size--;
            break;
        default:
            ops.push_back(og(idx));
            break;
        }
    }
    return ops;
}

// Helpers for the loop-built tests
static std::vector<Op>& operator+=(std::vector<Op>& a, const std::vector<Op>& b) {
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

int main() {
    // ------------------------------------------------------------------
    //  Tests 1-26: handcrafted. Each is named for the bug it hunts.
    //  Get these green first, in order.
    // ------------------------------------------------------------------
    TEST("empty: get(0)", {og(0)});
    TEST("empty: get(5)", {og(5)});
    TEST("empty: deleteAtIndex(0)", {od(0), og(0)});
    TEST("empty: addAtIndex(1) rejected", {oi(1, 9), og(0)});
    TEST("empty: addAtIndex(0) accepted", {oi(0, 9), og(0), og(1)});
    TEST("addAtTail on empty list", {ot(7), og(0), og(1)});
    TEST("addAtHead on empty list", {oh(7), og(0), og(1)});
    TEST("single element: delete then get", {oh(1), od(0), og(0)});

    TEST("delete only elem then addAtTail (stale tail)", {oh(1), od(0), ot(2), og(0), og(1)});
    TEST("delete only elem then addAtHead (stale tail)",
         {ot(1), od(0), oh(2), ot(3), og(0), og(1)});
    TEST("delete last elem then addAtTail",
         {oh(1), ot(2), ot(3), od(2), ot(4), og(0), og(1), og(2), og(3)});
    TEST("delete head then get all", {ot(1), ot(2), ot(3), od(0), og(0), og(1), og(2)});
    TEST("delete middle", {ot(1), ot(2), ot(3), od(1), og(0), og(1), og(2)});

    TEST("deleteAtIndex == size rejected (off-by-one)", {oh(1), oh(2), od(2), og(0), og(1), og(2)});
    TEST("get == size rejected (off-by-one)", {oh(1), oh(2), og(2)});
    TEST("addAtIndex == size is an append", {oh(1), oh(2), oi(2, 3), og(0), og(1), og(2)});
    TEST("addAtIndex > size rejected, count must not move", {oh(1), oi(5, 9), og(1), ot(2), og(1)});
    TEST("addAtIndex(0) is addAtHead", {ot(1), oi(0, 2), og(0), og(1)});
    TEST("rejected delete must not decrement count", {oh(1), od(9), od(9), og(0), ot(2), og(1)});

    TEST("LeetCode sample 1", {oh(1), ot(3), oi(1, 2), og(1), od(1), og(1)});

    {  // build up, then tear down from the front, then reuse the list
        std::vector<Op> ops;
        for (int i = 1; i <= 5; i++)
            ops.push_back(ot(i));
        for (int i = 0; i < 5; i++)
            ops.push_back(od(0));
        ops += {og(0), oh(99), og(0)};
        TEST("build up then tear down completely", ops);
    }
    {  // same, tearing down from the back
        std::vector<Op> ops;
        for (int i = 1; i <= 5; i++)
            ops.push_back(ot(i));
        for (int i = 0; i < 5; i++)
            ops.push_back(od(4 - i));
        ops += {og(0), ot(99), og(0)};
        TEST("tear down from the back", ops);
    }
    {
        std::vector<Op> ops = {oh(1), ot(2), oh(3), ot(4), oh(5)};
        for (int i = 0; i < 6; i++)
            ops.push_back(og(i));
        TEST("alternating head/tail then read every position", ops);
    }
    {
        std::vector<Op> ops;
        for (int i = 1; i <= 4; i++)
            ops.push_back(ot(i));
        ops += {oi(0, 100), oi(2, 200), oi(6, 300)};
        for (int i = 0; i < 8; i++)
            ops.push_back(og(i));
        TEST("insert at every position of a 4-list", ops);
    }
    {
        std::vector<Op> ops;
        for (int i = 0; i < 10; i++)
            ops += {oh(1), od(0)};
        ops += {og(0), ot(5), og(0)};
        TEST("repeated churn at head", ops);
    }
    {
        std::vector<Op> ops;
        for (int i = 0; i < 10; i++)
            ops += {ot(1), od(0)};
        ops += {og(0), oh(5), og(0)};
        TEST("repeated churn at tail", ops);
    }

    // ------------------------------------------------------------------
    //  Tests 27-92: randomised. Fixed seed, so failures reproduce exactly.
    //  Change the seed once you're passing for a fresh set.
    // ------------------------------------------------------------------
    std::mt19937 rng(20240707u);
    auto R = [&](int lo, int hi) { return (int)std::uniform_int_distribution<int>(lo, hi)(rng); };

    for (int i = 1; i <= 25; i++)  // tiny lists, heavy boundary pressure
        TEST("random tiny #" + std::to_string(i), randomOps(rng, R(5, 15), 2, false));
    for (int i = 1; i <= 21; i++)
        TEST("random small #" + std::to_string(i), randomOps(rng, R(20, 40), 3, false));
    for (int i = 1; i <= 15; i++)
        TEST("random medium #" + std::to_string(i), randomOps(rng, R(60, 120), 5, false));
    for (int i = 1; i <= 5; i++)
        TEST("random large #" + std::to_string(i), randomOps(rng, R(300, 600), 10, false));

    // ------------------------------------------------------------------
    //  Tests 93-100: negative indices. These are OUTSIDE LeetCode's stated
    //  constraints (it promises 0 <= index), so the judge accepts a solution
    //  that ignores them. An interviewer won't. Delete this block if you
    //  only care about getting accepted.
    // ------------------------------------------------------------------
    TEST("negative: get(-1)", {oh(1), og(-1)});
    TEST("negative: deleteAtIndex(-1)", {oh(1), od(-1), og(0)});
    TEST("negative: addAtIndex(-1)", {oh(1), oi(-1, 9), og(0), og(1)});
    for (int i = 1; i <= 5; i++)
        TEST("random negative #" + std::to_string(i), randomOps(rng, R(15, 40), 3, true));

    // ------------------------------------------------------------------
    std::cout << "\n========================================\n"
              << "passed:  " << g_passed << " / " << g_id << "\n"
              << "failed:  " << g_failed << "\n"
              << "ops run: " << g_ops << "\n"
              << "========================================\n";
    if (g_failed == 0)
        std::cout << "All good. Sanitizers found nothing either.\n";
    return g_failed == 0 ? 0 : 1;
}

// ============================================================================
//  SPOILER - a working sentinel solution. Paste over the stub above to
//  sanity-check the harness, or to diff against yours once it passes.
//  Stop reading here if you haven't solved it yet.
// ============================================================================
/*
class MyLinkedList {
    struct Node {
        int val;
        Node *prev, *next;
        Node(int v = 0) : val(v), prev(nullptr), next(nullptr) {}
    };
    Node *head, *tail;   // sentinels, never hold data
    int size;

    Node* nodeAt(int index) {                 // walk from the nearer end
        if (index < size - index) {
            Node* cur = head->next;
            for (int i = 0; i < index; i++) cur = cur->next;
            return cur;
        }
        Node* cur = tail;
        for (int i = size; i > index; i--) cur = cur->prev;
        return cur;
    }
    void insertBefore(Node* pos, int val) {
        Node* node = new Node(val);
        node->prev = pos->prev;
        node->next = pos;
        pos->prev->next = node;
        pos->prev = node;
        size++;
    }
    void unlink(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size--;
    }
public:
    MyLinkedList() : size(0) {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
    ~MyLinkedList() {
        Node* cur = head;
        while (cur) { Node* nxt = cur->next; delete cur; cur = nxt; }
    }
    int get(int index) {
        if (index < 0 || index >= size) return -1;
        return nodeAt(index)->val;
    }
    void addAtHead(int val) { insertBefore(head->next, val); }
    void addAtTail(int val) { insertBefore(tail, val); }
    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) return;
        insertBefore(index == size ? tail : nodeAt(index), val);
    }
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        unlink(nodeAt(index));
    }
};
*/