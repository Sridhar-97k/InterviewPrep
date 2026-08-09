# Two Pointers

## When to reach for it
- Sorted array/string and you need a pair/triplet with some property.
- In-place operations from both ends (reverse, palindrome check).
- Removing/partitioning elements without extra space (slow/fast pointers).

## Shapes
1. **Opposite ends** — `left = 0`, `right = n-1`, move inward. (reverse, two-sum on sorted, container with most water)
2. **Same direction (fast/slow)** — one scans, one writes. (remove duplicates, cycle detection in linked list)

## Complexity
Usually O(n) time, O(1) extra space.

## My solutions here
- `cpp/strings/ReverseVowelsInWord.cpp`, `cpp/strings/ReverseStringUsingRecursion.cpp`
- `java/src/com/prep/strings/ReverseString.java`
