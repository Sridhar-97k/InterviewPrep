package com.prep.legacy;

public class BinarySearchTree {
	void inorderDisplay(Node root) {
		if (root != null) {
			inorderDisplay(root.left);
			System.out.println("Data is " + root.data);
			inorderDisplay(root.right);
		}
	}

	void breadthWiseTraversal(Node root) {
		int height = getHeightOfTree(root);
		System.out.println("The tree height is" + height);
		for (int i = 1; i <= height; i++)
			printLevel(root, i);
	}

	private void printLevel(Node root, int i) {
		if (root == null)
			return;
		if (i == 1)
			System.out.println(root.data);
		else {
			printLevel(root.left, i - 1);
			printLevel(root.right, i - 1);
		}
	}

	private int getHeightOfTree(Node root) {
		if (root == null)
			return 0;
		int lHeight = getHeightOfTree(root.left), rHeight = getHeightOfTree(root.right);
		return lHeight > rHeight ? lHeight + 1 : rHeight + 1;
	}

	class Node {
		Node(double data) {
			this.data = data;
		}

		double data;
		Node left, right;
	}

	Node createNewNode(double data) {
		return new Node(data);
	}

	public Node addNode(Node root, double d) {
		if (root == null)
			return createNewNode(d);
		if (root.data > d)
			root.left = addNode(root.left, d);
		if (root.data < d)
			root.right = addNode(root.right, d);
		return root;
	}

	public void perform() {
		Node root = null;
		root = addNode(root, 10);
		root = addNode(root, 5);
		root = addNode(root, 20);
		root = addNode(root, 30);
		root = addNode(root, 7);
		breadthWiseTraversal(root);
	}

	public static void main(String args[]) {
		new BinarySearchTree().perform();
	}
}
