// Recursive C++ program to reverse a linked list
#include<iostream>
using namespace std;



class ReverseLinkListUsingRecursion {
	/* Link list node */
	struct Node {
		int data;
		struct Node* next;
		Node(int data)
		{
			this->data = data;
			next = NULL;
		}
	};

	struct LinkedList {
		Node* head;
		LinkedList() { head = NULL; }

		Node* reverse(Node* head)
		{
			cout << " \nInvoked reverse with value : " << head->data << endl;
			if (head == NULL || head->next == NULL)
			{
				cout << "\nReturning head " << head->data; // only last element can retun here
				return head;
			}
			/* reverse the rest list and put
			  the first element at the end */
			Node* rest = reverse(head->next);
			cout << "\nValue of rest is : " << rest->data << endl;
			cout << "\nValue of head here is : " << head->data << endl;
			head->next->next = head;

			/* tricky step -- see the diagram */
			head->next = NULL;

			/* fix the head pointer */
			return rest;
		}

		/* Function to print linked list */
		void print()
		{
			struct Node* temp = head;
			while (temp != NULL) {
				cout << temp->data << " ";
				temp = temp->next;
			}
		}

		void push(int data)
		{
			Node* temp = new Node(data);
			temp->next = head;
			head = temp;
		}
	};

	/* Driver program to test above function*/
public:  int perform()
{
	/* Start with the empty list */
	LinkedList ll;
	ll.push(20);
	ll.push(4);
	ll.push(15);
	ll.push(85);
	ll.push(115);


	cout << "Given linked list\n";
	ll.print();

	ll.head = ll.reverse(ll.head);

	cout << "\nReversed linked list \n";
	ll.print();
	return 0;
}
};
