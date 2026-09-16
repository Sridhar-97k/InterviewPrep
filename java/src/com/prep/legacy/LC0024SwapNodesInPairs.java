package com.prep.legacy;

class ListNode {
	int val;
	ListNode next;

	ListNode() {
	}

	ListNode(int val) {
		this.val = val;
	}

	ListNode(int val, ListNode next) {
		this.val = val;
		this.next = next;
	}
}

class LC0024SwapNodesInPairs {
	public void displayList(ListNode head) {
		System.out.println("\nThe list is");
		for (ListNode trav = head; trav != null; trav = trav.next)
			System.out.println(" " + trav.val + " ");
		System.out.println("");
	}

	public ListNode swapPairs(ListNode head) {
		ListNode temp;
		if (head == null || head.next == null) {
			System.out.println("Returning the base case " + head.val);
			return head;
		}
		temp = head.next;
		head.next = head.next.next;
		temp.next = head;
		head = temp;
		System.out.println("Inside the function ");
		displayList(head);
		head.next.next = swapPairs(head.next.next);
		return head;
	}

	public static void main(String[] args) {
		LC0024SwapNodesInPairs solution = new LC0024SwapNodesInPairs();
		ListNode head = new ListNode(10);
		head.next = new ListNode(20);
		head.next.next = new ListNode(30);
		head.next.next.next = new ListNode(40);
		head.next.next.next.next = new ListNode(50);
		solution.displayList(head);
		head = solution.swapPairs(head);
		solution.displayList(head);
	}
}
