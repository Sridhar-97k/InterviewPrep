package com.prep.legacy;

import java.util.Collections;
import java.util.PriorityQueue;

public class PriorityQueueTestClass {
	public static void main(String[] args) {
		PriorityQueue<String> queue = new PriorityQueue<String>(Collections.reverseOrder());
		queue.add("aa");
		queue.add("b");
		queue.add("cc");
		queue.add("D");
		queue.add("e");
		while (!queue.isEmpty())
			System.out.println(queue.poll());
		queue.poll();
	}
}
