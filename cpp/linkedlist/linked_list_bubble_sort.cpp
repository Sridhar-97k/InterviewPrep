// C++ program to illustrate linked list bubble sort
#include <iostream>

using namespace std;

class LinkListBubbleSort {
    typedef struct node {
        int val;
        struct node* next;

    } Node;

    Node* createNewNode(int val) {
        Node* temp = (Node*)malloc(sizeof(Node));

        temp->val = val;
        temp->next = NULL;

        return temp;
    }
    Node* insertAtTheEnd(Node* head, int dta)

    {
        cout << "Inserting " << dta << endl;
        ;
        Node* temp = createNewNode(dta);
        if (head == NULL) {
            return temp;
        }

        else {
            Node* traverse = head;
            while (traverse->next != NULL) {
                traverse = traverse->next;
            }
            traverse->next = temp;
            return head;
        }
    }
    void displayList(Node* head) {
        Node* traverse = head;
        cout << "The list is :" << endl;
        for (; traverse != NULL; traverse = traverse->next) {
            cout << traverse->val << endl;
        }
    }
    Node* swap(Node* first, Node* second) {

        Node* temp = second->next;
        second->next = first;
        first->next = temp;
        return second;
    }
    int countList(Node* head) {
        Node* traverse = head;
        int count = 0;
        for (; traverse != NULL; traverse = traverse->next) {
            ++count;
        }
        cout << "The count is " << count << endl;
        return count;
    }
    void bubbleSort(Node** head) {
        int count = countList(*head);

        for (int i = 0; i <= count; i++) {
            Node** h = head;
            int swapped = 0;
            for (int j = 0; j < (count - (i + 1)); j++) {
                Node* p1 = *h;
                Node* p2 = p1->next;
                if ((p2->val) < (p1->val)) {
                    *h = swap(p1, p2);
                    swapped = 1;
                    cout << p1->val << " swapped with " << p2->val << endl;
                }
                h = &(*h)->next;
            }
            if (swapped == 0)
                break;
        }
    }

    void insertAtTheEndUsingDoublePointer(Node** head, int dta) {
        cout << "Inserting " << dta << endl;
        ;
        Node* temp = createNewNode(dta);
        if (*head == NULL) {
            *head = temp;
        }

        else {
            Node* traverse = *head;
            while (traverse->next != NULL) {
                traverse = traverse->next;
            }
            traverse->next = temp;
        }
    }

  public:
    int perform() {

        Node* head = NULL;
        // head = insertAtTheEnd(head, 10);
        // head = insertAtTheEnd(head, 20);
        // head = insertAtTheEnd(head, 30);
        // head = insertAtTheEnd(head, 60);

        insertAtTheEndUsingDoublePointer(&head, rand() % 100);
        insertAtTheEndUsingDoublePointer(&head, rand() % 100);
        insertAtTheEndUsingDoublePointer(&head, rand() % 100);
        insertAtTheEndUsingDoublePointer(&head, rand() % 100);

        displayList(head);
        // bubbleSort(&head);
        displayList(head);
        return 0;
    }
};

int main() {
    LinkListBubbleSort solution;
    solution.perform();
    return 0;
}
