// =====================================================================
// LeetCode 55 - Jump Game  |  TEST DRIVER (no solution included)
// =====================================================================
//
// nums[i] is the maximum jump length from index i. Starting at index 0,
// return true if the last index is reachable.
// Constraints: 1 <= n <= 10^4, 0 <= nums[i] <= 10^5
//
// ---------------------------------------------------------------------
// USAGE
// ---------------------------------------------------------------------
// Put your solution in solution.h next to this file:
//
//     #pragma once
//     #include <vector>
//     class Solution {
//     public:
//         bool canJump(std::vector<int>& nums) { /* your code */ }
//     };
//
// Then:
//     g++ -std=c++17 -O2 -o jg1 0055_jump_game_test_driver.cpp && ./jg1
//
// A different header:
//     g++ -std=c++17 -O2 -DSOLUTION_HEADER='"my_sol.h"' -o jg1 0055_jump_game_test_driver.cpp
//
// The driver auto-detects whichever of these members exist and runs each
// one as a separate implementation, so you can race your variants:
//     canJump, can_jump, canJumpGreedy, canJumpBackwards, canJumpDP, solve
// Parameter may be std::vector<int>&, const&, or by value. Return type may
// be any type convertible to bool.
//
// Wrote a free function instead? Adapt it in one line:
//     class Solution { public:
//         bool canJump(std::vector<int>& v) { return ::canJump(v); } };
//
// FLAGS
//     --list            print the case table and exit
//     --case N          run a single case with detail
//     --fail-fast       stop at the first failure
//     -v, --verbose     print passing cases too
//     --timeout S       per-case limit in seconds, 0 disables (default 5)
//     --export          dump every case as "index expected n v1 v2 ..."
//
// Exit code is 0 when every case passes, 1 otherwise.
// =====================================================================

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#ifndef SOLUTION_HEADER
#define SOLUTION_HEADER "solution.h"
#endif
#include SOLUTION_HEADER

// ---------------------------------------------------------------------
// Per-case timeout (POSIX). Guards against solutions that never advance
// a pointer off a zero and spin forever. On other platforms the flag is
// accepted and ignored.
//
// Caveat: the alarm unwinds with siglongjmp, which does not run
// destructors in the interrupted call. Fine for a test rig; the process
// is about to move on to the next case either way.
// ---------------------------------------------------------------------
#if defined(__unix__) || defined(__APPLE__)
#define JG_HAVE_TIMEOUT 1
#include <csetjmp>
#include <csignal>
#include <sys/time.h>
static sigjmp_buf g_jumpBuf;
static volatile sig_atomic_t g_armed = 0;
static void jgOnAlarm(int) {
    if (g_armed) {
        g_armed = 0;
        siglongjmp(g_jumpBuf, 1);
    }
}
static void jgArm(double seconds) {
    struct itimerval it{};
    it.it_value.tv_sec = static_cast<time_t>(seconds);
    it.it_value.tv_usec = static_cast<suseconds_t>((seconds - it.it_value.tv_sec) * 1e6);
    g_armed = 1;
    setitimer(ITIMER_REAL, &it, nullptr);
}
static void jgDisarm() {
    struct itimerval it{};
    g_armed = 0;
    setitimer(ITIMER_REAL, &it, nullptr);
}
#else
#define JG_HAVE_TIMEOUT 0
static void jgArm(double) {}
static void jgDisarm() {}
#endif

// =====================================================================
// TEST DATA
// =====================================================================
struct Case {
    std::vector<int> nums;
    bool expected;
    std::string label;
};

static std::vector<int> rep(int value, int count) {
    return std::vector<int>(static_cast<size_t>(count), value);
}
static std::vector<int> cat(std::initializer_list<std::vector<int>> parts) {
    std::vector<int> out;
    for (const auto& p : parts)
        out.insert(out.end(), p.begin(), p.end());
    return out;
}
static std::vector<int> cycle(std::initializer_list<int> pattern, int times) {
    std::vector<int> out;
    out.reserve(pattern.size() * static_cast<size_t>(times));
    for (int t = 0; t < times; ++t)
        for (int v : pattern)
            out.push_back(v);
    return out;
}
static std::vector<int> descending(int from) {  // from, from-1, ..., 0
    std::vector<int> out;
    out.reserve(static_cast<size_t>(from) + 1);
    for (int v = from; v >= 0; --v)
        out.push_back(v);
    return out;
}

static std::vector<Case> explicitCases() {
    return {
        // --- LeetCode samples -----------------------------------------
        {{2, 3, 1, 1, 4}, true, "LC example 1"},
        {{3, 2, 1, 0, 4}, false, "LC example 2 - trapped by the 0"},
        // --- minimal / boundary ---------------------------------------
        {{0}, true, "single element, already at the end"},
        {{1}, true, "single element with a step"},
        {{100000}, true, "single element, max value"},
        {{0, 1}, false, "cannot leave index 0"},
        {{1, 0}, true, "exactly one hop"},
        {{2, 0}, true, "overshoot allowed"},
        {{0, 0}, false, "two zeros"},
        {{1, 1}, true, "two ones"},
        // --- zeros in awkward places ----------------------------------
        {{1, 1, 1, 1}, true, "all ones"},
        {{1, 1, 0, 1}, false, "zero one before the end"},
        {{1, 1, 1, 0}, true, "trailing zero is harmless"},
        {{1, 1, 0, 0}, false, "two trailing zeros"},
        {{2, 0, 0}, true, "land exactly on the last index"},
        {{2, 0, 0, 0}, false, "one index short"},
        {{3, 0, 0, 0}, true, "reach the end in a single jump"},
        {{5, 0, 0, 0, 0, 0}, true, "big first jump clears all zeros"},
        {{1, 0, 1, 0}, false, "stuck at index 1"},
        {{0, 2, 3}, false, "leading zero"},
        {{0, 0, 0, 0, 0}, false, "all zeros"},
        {{4, 0, 0, 0, 0}, true, "first value exactly spans the array"},
        {{3, 0, 0, 0, 0}, false, "first value one short"},
        // --- frontier, not local maximum ------------------------------
        {{2, 5, 0, 0}, true, "detour through the big value"},
        {{2, 1, 0, 3}, false, "small value first kills it"},
        {{2, 1, 1, 0}, true, "chain of small hops works"},
        {{3, 1, 0, 0, 4}, false, "frontier stalls at index 3"},
        {{4, 1, 0, 0, 4}, true, "frontier just barely reaches"},
        {{1, 3, 0, 0, 0}, true, "second element rescues the run"},
        {{2, 0, 1, 0, 1}, false, "reachable prefix stops at 3"},
        {{2, 0, 2, 0, 1}, true, "index 2 extends the frontier"},
        {{1, 2, 0, 1}, true, "skip over the zero"},
        {{3, 2, 1, 0, 0}, false, "classic dead zero"},
        {{2, 3, 0, 1, 4}, true, "zero is jumped over"},
        {{1, 2, 3}, true, "increasing"},
        {{3, 2, 1}, true, "decreasing but wide enough"},
        {{1, 2, 1, 1, 1}, true, "mixed small values"},
        {{10, 1, 1, 1, 1}, true, "huge head"},
        {{1, 0, 0, 0, 10}, false, "huge tail is unreachable"},
        {{1, 1, 2, 2, 0, 1, 1}, true, "zero mid-array, still fine"},
        {{2, 1, 1, 1, 1}, true, "uniform small steps"},
        {{5, 4, 3, 2, 1, 0, 0}, false, "descending run dies on the zeros"},
        {{5, 4, 3, 2, 1, 0}, true, "descending run lands exactly"},
        {{1, 5, 2, 1, 0, 2, 0}, true, "index 1 clears everything"},
        {{4, 1, 1, 0, 0, 0, 0}, false, "frontier caps at index 4"},
        {{1, 2, 0, 0, 1, 0, 0, 1}, false, "long tail unreachable past index 3"},
        // --- large / structured ---------------------------------------
        {rep(1, 1000), true, "1000 ones"},
        {cat({rep(1, 999), {0}}), true, "ones then trailing zero"},
        {cat({rep(1, 500), {0}, rep(1, 499)}), false, "zero wall in the middle"},
        {rep(2, 5000), true, "5000 twos"},
        {cat({{0}, rep(1, 100)}), false, "leading zero, long tail"},
        {cat({{100}, rep(0, 99)}), true, "one jump over 99 zeros"},
        {cat({{100}, rep(0, 200)}), false, "jump falls short of a long tail"},
        {cat({{100000}, rep(0, 9999)}), true, "max value, max length"},
        {descending(2999), true, "strictly decreasing, always reachable"},
        {cat({rep(1, 9999), {0}}), true, "worst case for a linear scan"},
        {cycle({2, 0}, 2500), true, "alternating 2,0 pattern"},
        {cycle({1, 0}, 2500), false, "alternating 1,0 pattern dies at index 1"},
        {cat({{3}, cycle({0, 0, 3}, 100)}), true, "periodic pattern that stays alive"},
        {cat({{3}, cycle({0, 0, 0}, 100)}), false, "periodic pattern of dead zeros"},
    };
}

// ---------------------------------------------------------------------
// Deterministic generated inputs.
//
// splitmix64 rather than std::mt19937 + uniform_int_distribution: the
// standard distributions are implementation-defined, so libstdc++ and
// libc++ would produce different arrays and the baked-in expected values
// below would stop matching. This generator is byte-identical everywhere.
// ---------------------------------------------------------------------
struct SplitMix64 {
    unsigned long long state;
    explicit SplitMix64(unsigned long long seed) : state(seed) {}
    unsigned long long next() {
        unsigned long long z = (state += 0x9E3779B97F4A7C15ULL);
        z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
        z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
        return z ^ (z >> 31);
    }
    int below(int bound) {
        return static_cast<int>(next() % static_cast<unsigned long long>(bound));
    }
    int between(int lo, int hi) {
        return lo + below(hi - lo + 1);
    }
};

static const int kRandomCount = 40;

static std::vector<std::pair<std::vector<int>, std::string>> randomInputs() {
    SplitMix64 rng(55);
    const int sizes[] = {2, 3, 5, 8, 12, 20, 50, 120, 400};
    std::vector<std::pair<std::vector<int>, std::string>> built;
    for (int k = 0; k < kRandomCount; ++k) {
        int n = sizes[rng.below(9)];
        std::vector<int> nums(static_cast<size_t>(n));
        if (k % 4 == 0) {  // very sparse, lots of zeros
            const int pool[] = {0, 0, 0, 1, 2};
            for (int& v : nums)
                v = pool[rng.below(5)];
        } else if (k % 4 == 1) {  // small values
            for (int& v : nums)
                v = rng.between(0, 3);
        } else if (k % 4 == 2) {  // medium values
            int hi = std::max(1, n / 4);
            for (int& v : nums)
                v = rng.between(0, hi);
        } else {  // mostly positive, a few zeros
            for (int& v : nums)
                v = rng.between(1, 4);
            for (int t = 0; t < n / 5; ++t)
                nums[static_cast<size_t>(rng.below(n))] = 0;
        }
        built.emplace_back(std::move(nums),
                           "random #" + std::to_string(k + 1) + " (n=" + std::to_string(n) + ")");
    }
    return built;
}

// Expected answers for randomInputs(), in order. Verified against an
// O(n^2) reachability DP cross-checked with a linear pass. Do not edit
// by hand: regenerate with --export if the generator ever changes.
static const bool kRandomExpected[kRandomCount] = {
    false, true, true,  false, false, false, true,  true,  false, false,
    true,  true, false, false, true,  false, false, false, true,  false,
    false, true, false, true,  false, false, true,  false, false, false,
    true,  true, false, false, false, false, false, true,  true,  true,
};

static std::vector<Case> buildCases() {
    std::vector<Case> cases = explicitCases();
    auto generated = randomInputs();
    if (static_cast<int>(generated.size()) != kRandomCount) {
        std::fprintf(stderr, "test data out of sync: regenerate kRandomExpected\n");
        std::exit(2);
    }
    for (int i = 0; i < kRandomCount; ++i)
        cases.push_back({generated[static_cast<size_t>(i)].first, kRandomExpected[i],
                         generated[static_cast<size_t>(i)].second});
    return cases;
}

// =====================================================================
// SOLUTION DISCOVERY (compile-time)
// =====================================================================
struct Impl {
    std::string name;
    std::function<bool(std::vector<int>&)> run;
};

// Detects `S{}.NAME(vector<int>&)` for any return type convertible to bool.
#define JG_DETECT(NAME)                                                                            \
    template <class S, class = void> struct jg_has_##NAME : std::false_type {};                    \
    template <class S>                                                                             \
    struct jg_has_##NAME<                                                                          \
        S, std::void_t<decltype(std::declval<S&>().NAME(std::declval<std::vector<int>&>()))>>      \
        : std::true_type {};

JG_DETECT(canJump)
JG_DETECT(can_jump)
JG_DETECT(canJumpGreedy)
JG_DETECT(canJumpBackwards)
JG_DETECT(canJumpDP)
JG_DETECT(solve)
#undef JG_DETECT

#define JG_REGISTER(NAME)                                                                          \
    if constexpr (jg_has_##NAME<S>::value) {                                                       \
        out.push_back({#NAME, [](std::vector<int>& a) -> bool {                                    \
                           S s;                                                                    \
                           return static_cast<bool>(s.NAME(a));                                    \
                       }});                                                                        \
    }

template <class S> static std::vector<Impl> collect() {
    std::vector<Impl> out;
    JG_REGISTER(canJump)
    JG_REGISTER(can_jump)
    JG_REGISTER(canJumpGreedy)
    JG_REGISTER(canJumpBackwards)
    JG_REGISTER(canJumpDP)
    JG_REGISTER(solve)
    return out;
}
#undef JG_REGISTER

// =====================================================================
// RUNNER
// =====================================================================
enum class Status { Ok, Wrong, Threw, TimedOut };

struct Outcome {
    Status status = Status::Ok;
    bool got = false;
    std::string detail;
    double millis = 0.0;
    bool mutated = false;
};

static std::string preview(const std::vector<int>& nums, size_t width = 62) {
    std::string text = "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i)
            text += ", ";
        if (text.size() > width) {
            text += "...";
            break;
        }
        text += std::to_string(nums[i]);
    }
    return text + "]";
}

static Outcome runOne(const Impl& impl, const Case& tc, double timeout) {
    Outcome result;
    std::vector<int> supplied = tc.nums;

#if JG_HAVE_TIMEOUT
    if (timeout > 0) {
        std::signal(SIGALRM, jgOnAlarm);
        if (sigsetjmp(g_jumpBuf, 1) != 0) {
            jgDisarm();
            result.status = Status::TimedOut;
            result.millis = timeout * 1000.0;
            char buf[96];
            std::snprintf(buf, sizeof(buf), "timed out after %gs (infinite loop?)", timeout);
            result.detail = buf;
            return result;
        }
        jgArm(timeout);
    }
#else
    (void)timeout;
#endif

    auto start = std::chrono::steady_clock::now();
    bool got = false;
    try {
        got = impl.run(supplied);
    } catch (const std::exception& e) {
        jgDisarm();
        result.status = Status::Threw;
        result.detail = std::string("threw std::exception: ") + e.what();
        return result;
    } catch (...) {
        jgDisarm();
        result.status = Status::Threw;
        result.detail = "threw a non-standard exception";
        return result;
    }
    auto finish = std::chrono::steady_clock::now();
    jgDisarm();

    result.millis = std::chrono::duration<double, std::milli>(finish - start).count();
    result.got = got;
    result.mutated = (supplied != tc.nums);
    if (got != tc.expected) {
        result.status = Status::Wrong;
        result.detail = "wrong answer";
    }
    return result;
}

static const char* boolText(bool value) {
    return value ? "true" : "false";
}

static int runSuite(const std::vector<Impl>& impls, const std::vector<Case>& cases, bool failFast,
                    bool verbose, double timeout) {
    bool anyFailure = false;

    for (const Impl& impl : impls) {
        std::vector<std::pair<int, Outcome>> failures;
        std::vector<int> mutations;
        double slowest = 0.0, total = 0.0;
        std::string slowestLabel;
        int ran = 0;

        for (size_t i = 0; i < cases.size(); ++i) {
            Outcome out = runOne(impl, cases[i], timeout);
            ++ran;
            total += out.millis;
            if (out.millis > slowest) {
                slowest = out.millis;
                slowestLabel = "#" + std::to_string(i + 1) + " " + cases[i].label;
            }
            if (out.mutated)
                mutations.push_back(static_cast<int>(i + 1));
            if (out.status != Status::Ok) {
                failures.emplace_back(static_cast<int>(i + 1), out);
                if (failFast)
                    break;
            } else if (verbose) {
                std::printf("  ok  #%3zu %s\n", i + 1, cases[i].label.c_str());
            }
        }

        std::printf("\n[%s]  %d/%d passed   total %.1f ms   slowest %.2f ms (%s)   %s",
                    impl.name.c_str(), ran - static_cast<int>(failures.size()), ran, total, slowest,
                    slowestLabel.c_str(), failures.empty() ? "PASS" : "FAIL");
        if (ran < static_cast<int>(cases.size()))
            std::printf(" (stopped early after %d cases)", ran);
        std::printf("\n");

        if (!mutations.empty()) {
            std::printf("  warning: input vector was modified on case(s)");
            for (size_t i = 0; i < mutations.size() && i < 8; ++i)
                std::printf(" %d", mutations[i]);
            std::printf("%s\n", mutations.size() > 8 ? " ..." : "");
        }

        size_t shown = 0;
        for (const auto& entry : failures) {
            if (shown++ >= 25)
                break;
            const Case& tc = cases[static_cast<size_t>(entry.first - 1)];
            const Outcome& out = entry.second;
            std::printf("\n  #%d %s  [%s]\n", entry.first, tc.label.c_str(), out.detail.c_str());
            std::printf("     n        = %zu\n", tc.nums.size());
            std::printf("     nums     = %s\n", preview(tc.nums).c_str());
            std::printf("     expected = %s\n", boolText(tc.expected));
            if (out.status == Status::Wrong)
                std::printf("     got      = %s\n", boolText(out.got));
            else
                std::printf("     got      = <no result>\n");
        }
        if (failures.size() > 25)
            std::printf("\n  ... and %zu more failures\n", failures.size() - 25);

        anyFailure = anyFailure || !failures.empty();
    }
    return anyFailure ? 1 : 0;
}

static void listCases(const std::vector<Case>& cases) {
    std::printf("%4s  %6s  %6s  label\n", "#", "n", "expect");
    for (size_t i = 0; i < cases.size(); ++i)
        std::printf("%4zu  %6zu  %6s  %s\n", i + 1, cases[i].nums.size(),
                    boolText(cases[i].expected), cases[i].label.c_str());
    std::printf("\n%zu cases total\n", cases.size());
}

static void exportCases(const std::vector<Case>& cases) {
    for (size_t i = 0; i < cases.size(); ++i) {
        std::printf("%zu %d %zu", i + 1, cases[i].expected ? 1 : 0, cases[i].nums.size());
        for (int v : cases[i].nums)
            std::printf(" %d", v);
        std::printf("\n");
    }
}

int main(int argc, char** argv) {
    bool failFast = false, verbose = false, wantList = false, wantExport = false;
    double timeout = 5.0;
    int single = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--list")
            wantList = true;
        else if (arg == "--export")
            wantExport = true;
        else if (arg == "--fail-fast")
            failFast = true;
        else if (arg == "-v" || arg == "--verbose")
            verbose = true;
        else if (arg == "--case" && i + 1 < argc)
            single = std::atoi(argv[++i]);
        else if (arg == "--timeout" && i + 1 < argc)
            timeout = std::atof(argv[++i]);
        else {
            std::fprintf(stderr, "unknown argument: %s\n", arg.c_str());
            return 2;
        }
    }

    std::vector<Case> cases = buildCases();

    if (wantList) {
        listCases(cases);
        return 0;
    }
    if (wantExport) {
        exportCases(cases);
        return 0;
    }

    std::vector<Impl> impls = collect<Solution>();
    if (impls.empty()) {
        std::fprintf(stderr, "no candidate method found on class Solution.\n"
                             "expose one of: canJump, can_jump, canJumpGreedy, "
                             "canJumpBackwards, canJumpDP, solve\n"
                             "taking std::vector<int>& and returning something "
                             "convertible to bool.\n");
        return 2;
    }

#if !JG_HAVE_TIMEOUT
    if (timeout > 0)
        std::printf("note: per-case timeout unavailable on this platform, ignoring --timeout\n");
#endif

    if (single) {
        if (single < 1 || single > static_cast<int>(cases.size())) {
            std::fprintf(stderr, "case must be 1..%zu\n", cases.size());
            return 2;
        }
        const Case& tc = cases[static_cast<size_t>(single - 1)];
        std::printf("case #%d: %s\n", single, tc.label.c_str());
        std::printf("  nums     = %s\n", preview(tc.nums, 200).c_str());
        std::printf("  expected = %s\n", boolText(tc.expected));
        int bad = 0;
        for (const Impl& impl : impls) {
            Outcome out = runOne(impl, tc, timeout);
            std::printf("  [%s] got %s  (%.3f ms)  %s%s\n", impl.name.c_str(),
                        out.status == Status::Ok || out.status == Status::Wrong ? boolText(out.got)
                                                                                : "<none>",
                        out.millis, out.status == Status::Ok ? "ok" : out.detail.c_str(),
                        out.mutated ? "  [MODIFIED INPUT]" : "");
            if (out.status != Status::Ok)
                bad = 1;
        }
        return bad;
    }

    std::printf("Jump Game I  -  %zu cases (%zu handwritten, %d generated)\n", cases.size(),
                cases.size() - kRandomCount, kRandomCount);
    std::printf("implementations: ");
    for (size_t i = 0; i < impls.size(); ++i)
        std::printf("%s%s", i ? ", " : "", impls[i].name.c_str());
    std::printf("\n");

    return runSuite(impls, cases, failFast, verbose, timeout);
}