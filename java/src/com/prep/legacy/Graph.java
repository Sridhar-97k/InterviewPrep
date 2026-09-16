package com.prep.legacy;

import java.util.ArrayList;
import java.util.LinkedList;

public class Graph {
	int vertices[];
	ArrayList<LinkedList<Integer>> edges;

	Graph(int v) {
		vertices = new int[v];
		edges = new ArrayList<LinkedList<Integer>>();
	}

	public static void name() {
	}
}
