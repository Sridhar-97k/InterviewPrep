#include <iostream>
#include <vector>

struct Node {
    int data;
    Node *next, *prev;
};
Node* createNewNode(int val) {
    Node* temp = (Node*)malloc(sizeof(Node));

    temp->data = val;

    temp->next = temp->prev = NULL;
    return temp;
}
