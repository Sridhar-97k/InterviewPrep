package com.prep.legacy;

public class BubbleSort {
	public static void main(String args[]) {
		int num[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
		System.out.println("The array is before processing");
		for (int i = 0; i < num.length; i++)
			System.out.print(" " + num[i] + " ");
		System.out.println("\n");
		BubbleSort bubblesort = new BubbleSort();
		bubblesort.sort(num);
		System.out.println("The array is after processing");
		for (int j = 0; j < num.length; j++)
			System.out.print(" " + num[j] + " ");
		System.out.println("\n");
	}

	private void swap(int a, int b) {
		int temp = a;
		a = b;
		b = temp;
	}

	private void sort(int[] num) {
		int temp;
		for (int i = 0; i < num.length; i++) {
			for (int j = 0; j < (num.length - 1); j++)
				if (num[j] > num[j + 1]) {
					temp = num[j];
					num[j] = num[j + 1];
					num[j + 1] = temp;
				}
			System.out.println("The array is ");
			for (int ci = 0; ci < num.length; ci++)
				System.out.print(" " + num[ci] + " ");
		}
	}
}
