package com.prep.legacy;

class LC0088MergeSortedArray {
	public void merge(int[] array1, int m, int[] array2, int n) {
		for (int a = 0, b = 0; b != array2.length && a != array1.length;) {
			if (array1[a] < array2[b]) {
				a++;
				System.out.println("\nIncrementing the index for first list " + a);
			} else if (array1[a] > array2[b]) {
				System.out.println("Shifting right by one");
				shiftToTheRightByOne(array1, a);
				array1[b] = array2[b];
				System.out.println("The number copied is " + array2[b]);
				b++;
			} else {
				System.out.println("Equal: " + array1[a] + "," + array2[b]);
				shiftToTheRightByOne(array1, a);
				array1[b] = array2[b];
				a++;
				b++;
			}
		}
		System.out.println("The array is finally: ");
		for (int i = 0; i < array1.length; i++)
			System.out.print(" " + array1[i] + " ");
	}

	private void shiftToTheRightByOne(int[] array, int index) {
		System.out.println("\nThe array before shifting");
		for (int i = 0; i < array.length; i++)
			System.out.print(" " + array[i] + " ");
		for (int i = (array.length - 1); i > index; i--)
			array[i] = array[i - 1];
		System.out.println("The array after shifting");
		for (int i = 0; i < array.length; i++)
			System.out.print(" " + array[i] + " ");
	}

	public static void main(String args[]) {
		int[] array1 = { 1, 2, 3, 0, 0, 0 }, array2 = { 2, 5, 6 };
		new LC0088MergeSortedArray().merge(array1, 3, array2, 3);
	}
}
