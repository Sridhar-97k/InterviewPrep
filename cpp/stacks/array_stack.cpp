#include <iostream>
#include <vector>

class myStack

{
  public:
    int top = -1;
    int capacity;
    int* arr;
    myStack(int cap) : capacity(cap) {
        arr = new int[cap];
    }

    void push(int x) {
        if (top + 1 == capacity) {
            std::cout << "At capacity, cannot insert" << std::endl;

        } else {
            arr[++top] = x;
        }
    }
    int pop() {
        if (top == -1) {
            std::cout << "stack empty, cannot pop" << std::endl;
            return -1;
        } else {
            return arr[top--];
        }
    }
    void displayStack() {
        std::cout << "The stack is " << std::endl;

        for (int i = 0; i <= top; i++) {
            std::cout << " (" << i << ") " << arr[i];
        }
    }
};

int main() {
    myStack myStack1(10);
    myStack1.push(10);
    myStack1.push(11);
    myStack1.push(12);
    myStack1.push(13);
    myStack1.displayStack();
}