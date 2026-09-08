#include <iostream>
struct ListNode {
  public:
    ListNode* next;
    int val;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// using hare and tortoise algorithm
int getDataAtMiddle(ListNode* head) {

    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow->val;
}
ListNode* createNewNode(int data) {
    ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
    temp->val = data;
    temp->next = NULL;

    return temp;
}
ListNode* insertAtTheHead(ListNode* head, int data_to_insert) {
    ListNode* newNode = createNewNode(data_to_insert);
    newNode->next = head;
    head = newNode;
    return head;
}
// Insert a new ListNode into the 'n' the position of the list, n = 1 -> insert into the head of the
// list
ListNode* insertAtAPosition(ListNode* head, int data, int position) {

    ListNode* trav = head;
    if (!head) {
        std::cout << "Empty List";

    } else if (position == 1)
        return insertAtTheHead(head, data);
    else {
        int i = 1;
        while (trav != NULL) {
            if (position == (i + 1)) {
                ListNode* temp = createNewNode(data);
                temp->next = trav->next;
                trav->next = temp;
                return head;
            }
            trav = trav->next;
            i = i + 1;
        }
    }
    return NULL;
}
ListNode* insertAtTheEnd(ListNode* head, int data) {
    ListNode* trav = head;

    while (trav->next != NULL)
        trav = trav->next;
    trav->next = createNewNode(data);
    return head;
}
ListNode* deleteFromBeginning(ListNode* head) {
    std::cout << "Deleting from the head" << std::endl;
    head = head->next;
    return head;
}

ListNode* deleteFromAParticularPosition(ListNode* head, int position) {
    std::cout << "Deleting from position " << position << std::endl;
    int i = 1;
    ListNode *trav = head, *prev = head;
    if (position == 1)
        return deleteFromBeginning(head);
    while (trav->next != NULL) {
        if (position == (i)) {
            std::cout << "Deleting the value " << trav->val << " from the list" << std::endl;
            prev->next = trav->next;
            return head;
        }
        prev = trav;
        trav = trav->next;
        i++;
    }
}
ListNode* deleteANodeHavingValue(ListNode* head, int value) {
    std::cout << "Deleting a ListNode having value " << value << std::endl;
    ListNode* trav = head;
    ListNode* prev = trav;
    while (trav->next != NULL) {
        if (trav->val == value) {
            prev->next = trav->next;
            std::cout << "The value " << value << " was deleted" << std::endl;
            return head;
        }
        prev = trav;
        trav = trav->next;
    }
    return NULL;
}
void printList(ListNode* head) {
    std::cout << "The linked list is " << std::endl;
    ListNode* trav = head;

    // for (; trav->next != NULL : trav = trav->next) {

    // }
    while (trav != NULL) {
        std::cout << trav->val << " ";
        trav = trav->next;
    }
    std::cout << std::endl;
}
int getKthNodeFromTheBeginning(ListNode* head, int position) {
    ListNode* trav = head;
    int iter_position = 1;
    while (trav->next != NULL) {
        if (iter_position == position) {

            return trav->val;
        }

        iter_position++;
    }
    return -1;
}
ListNode* reverseRecursiveLinkedList(ListNode* head)

{
    if (head == NULL || head->next == NULL)
        return head;
    ListNode* rest = reverseRecursiveLinkedList(head->next);
    head->next->next = head;
    head->next = NULL;
    return rest;
}
ListNode* reverseIterativeLinkedList(ListNode* head)

{
    ListNode *prev = NULL, *curr = head, *next;

    while (curr != NULL) {
        // std::cout << "Current ListNode = " << curr->data << " and address is " << curr << ", next
        // is
        // "
        //           << curr->next->data << " address is " << curr->next << std::endl;
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

    ListNode dummy(0);
    ListNode* nextPtr = &dummy;
    ListNode newNode;
    ListNode *trav1 = list1, *trav2 = list2;

    while (trav1 && trav2) {
        if (trav1->val < trav2->val) {
            newNode = ListNode(trav1->val);
            nextPtr->next = &newNode;
            nextPtr = nextPtr->next;
            trav1 = trav1->next;

        } else if (trav1->val >= trav2->val) {
            newNode = ListNode(trav2->val);
            nextPtr->next = &newNode;
            nextPtr = nextPtr->next;
            trav2 = trav2->next;
        }
    }
    while (trav1) {
        newNode = ListNode(trav1->val);
        nextPtr->next = &newNode;
        nextPtr = nextPtr->next;
        trav1 = trav1->next;
    }
    while (trav2) {
        newNode = ListNode(trav2->val);
        nextPtr->next = &newNode;
        nextPtr = nextPtr->next;
        trav2 = trav2->next;
    }
    return dummy.next;
}
ListNode* removeDuplicatesFromSortedList(ListNode* head) {
    ListNode* trav = head;
    ListNode* prev = NULL;
    while (trav) {
        // if trav->val == prev->val
        if (prev && (trav->val == prev->val)) {
            while ((trav->next) && trav->val == trav->next->val) {
                trav = trav->next;
            }

            prev->next = trav->next;
        }

        prev = trav;
        trav = trav->next;
    }

    return head;
}
ListNode* removeLinkedListElements(ListNode* head, int val) {

    if (!head || (head->val == val && head->next == nullptr)) {

        return nullptr;
    }
    ListNode* trav = head;
    ListNode* prev = trav;
    while (trav) {
        // if trav->val == prev->val
        if (val == trav->val) {

            prev->next = trav->next;
            trav = trav->next;
            continue;
        }

        prev = trav;
        trav = trav->next;
    }
    return head;
}

int main() {

    // ListNode* head = createNewNode(10);
    // printList(head);
    // head = insertAtTheEnd(head, 23);
    // head = insertAtTheEnd(head, 21);
    // head = insertAtTheEnd(head, 25);
    // head = insertAtTheEnd(head, 27);
    // printList(head);
    // std::cout << "Inserting 33 at position 2" << std::endl;
    // head = insertAtAPosition(head, 33, 2);

    // printList(head);
    // std::cout << "Deleting from beginning" << std::endl;
    // head = deleteFromBeginning(head);
    // printList(head);
    // std::cout << "Deleting from position 3" << std::endl;
    // head = deleteFromAParticularPosition(head, 3);
    // printList(head);
    // std::cout << "Inserting 45 at positin 2" << std::endl;
    // head = insertAtAPosition(head, 45, 2);
    // printList(head);
    // printList(head);
    // head = insertAtTheEnd(head, 23);
    // // head = insertAtTheEnd(head, 21);
    // // head = insertAtTheEnd(head, 25);
    // // head = insertAtTheEnd(head, 27);

    // printList(head);
    // std::cout << "The middle data is " << getDataAtMiddle(head) << std::endl;
    // printList(head);
    // head = reverseRecursiveLinkedList(head);
    // printList(head);
    // std::cout << "===========================" << std::endl;
    // head = reverseIterativeLinkedList(head);
    // std::cout << "===========================" << std::endl;
    // printList(head);
    // ListNode* head = createNewNode(10);
    // printList(head);
    ListNode* head = createNewNode(7);
    head = insertAtTheEnd(head, 7);
    head = insertAtTheEnd(head, 7);
    // head = insertAtTheEnd(head, 21);
    // head = insertAtTheEnd(head, 25);
    // head = insertAtTheEnd(head, 27);
    // head = insertAtTheEnd(head, 21);
    printList(head);
    // head = removeDuplicatesFromSortedList(head);
    // hea std::cout << "The list after removal of duplicates is " << std::endl;
    head = removeLinkedListElements(head, 7);
    printList(head);

    return 0;
}