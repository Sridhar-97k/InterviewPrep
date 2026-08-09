# InterviewPrep

A collection of my solutions to coding-interview problems (mostly LeetCode),
in **C++** and **Java**. You'll find a mixture of solution code and driver code.

## Layout

```
cpp/                 C++ solutions, grouped by pattern/topic
  arrays/  strings/  linked_lists/  dp/  ...
  include/           shared headers (ListNode.h, TreeNode.h)
  InterviewPrep.cpp  aggregator with a main() driver
java/
  src/com/prep/      Java solutions by topic; common/ has shared nodes
notes/               one markdown per recurring pattern
scripts/             misc helper scripts
.vscode/             shared build/debug config + code snippets
```

## Conventions

- One self-contained file per problem: a solution class exposing `perform()`,
  and a free `main()` at the bottom that runs it. Each file compiles and runs
  on its own.
- Name files after the problem (optionally `NNNN_Title` with the LeetCode number).
- Group by **pattern/topic**, not by difficulty — makes review by technique easy.
- Shared boilerplate (`ListNode`, `TreeNode`) lives in `cpp/include` and
  `java/src/com/prep/common`.

## Building

**C++** (WSL / g++) — build and run a single file:
```
g++ -std=c++20 -Wall -Wextra -g -Icpp/include cpp/strings/Flowerbed.cpp -o build/Flowerbed
./build/Flowerbed
```
In VS Code: open the file and press `Ctrl+Shift+B` — the "build & run current
file" task compiles it into `build/` and runs it. Type `sol` for the solution snippet.

**Java**:
```
javac -d build/java java/src/com/prep/strings/ReverseString.java
java -cp build/java com.prep.strings.ReverseString
```
