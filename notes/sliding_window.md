# Sliding Window

## When to reach for it
- Contiguous subarray/substring problem asking for a max/min length, sum, or count.
- "Longest/shortest substring with condition", "max sum of size-k window".

## Shapes
1. **Fixed size k** — slide the window, add the entering element, drop the leaving one.
2. **Variable size** — expand `right`; while the window is invalid, shrink from `left`.

## Template (variable window)
```
left = 0
for right in range(n):
    add s[right] to window
    while window invalid:
        remove s[left]; left++
    update answer with (right - left + 1)
```

## Complexity
O(n) time — each element enters and leaves the window at most once.
