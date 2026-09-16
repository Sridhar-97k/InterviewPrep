package com.prep.legacy;

public class LC0027RemoveElement {
	void shiftToTheLeftByOne(int nums[]) {
		for (int i = 0; i < (nums.length - 1); i++)
			nums[i] = nums[i + 1];
	}

	void shiftToTheRightByOne(int nums[]) {
		for (int i = (nums.length - 1); i > 0; i--)
			nums[i] = nums[i - 1];
	}

	void shiftToTheLeftByOneAtIndex(int index, int nums[]) {
		int toShift = index - 0;
		for (int i = 0; i < (nums.length - 1); i++)
			nums[i] = nums[i + 1];
	}

	void shiftToTheRightByOneAtIndex(int index, int nums[]) {
		int toShift = nums.length - index - 1;
		System.out.println("to shift" + toShift);
		for (int i = index; i < nums.length; i++)
			nums[index + i] = nums[index + i - 1];
	}

	public int removeElement(int[] nums, int val) {
		int counter = 0;
		shiftToTheRightByOneAtIndex(1, nums);
		return counter;
	}

	public void displayArray(int nums[]) {
		System.out.println("The array is ");
		for (int i = 0; i < nums.length; i++)
			System.out.print(nums[i] + " ");
		System.out.println("\n");
	}

	public static void main(String[] args) {
		LC0027RemoveElement solution = new LC0027RemoveElement();
		int array[] = { 0, 9, 3, 4, 7, 2, 4, 5, 3 };
		int value = 3;
		solution.displayArray(array);
		System.out.println(solution.removeElement(array, value));
		solution.displayArray(array);
	}
}
