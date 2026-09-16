package com.prep.legacy;

class ListNode1 {
	int val;
	ListNode1 next;

	ListNode1() {
	}

	ListNode1(int val) {
		this.val = val;
	}

	ListNode1(int val, ListNode1 next) {
		this.val = val;
		this.next = next;
	}
}

public class LC0206ReverseLinkedList {
	public static void main(String[] args) {
		LC0206ReverseLinkedList reverse = new LC0206ReverseLinkedList();
		ListNode1 head = new ListNode1(10);
		head.next = new ListNode1(20);
		head.next.next = new ListNode1(30);
		head.next.next.next = new ListNode1(40);
		head.next.next.next.next = new ListNode1(50);
	}
}
