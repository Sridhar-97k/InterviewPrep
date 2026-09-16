package com.prep.legacy;

class LC0605CanPlaceFlowers {
	boolean canPlaceFlowerHere(int flowerbed[], int position) {
		System.out.println("Position " + position);
		if (flowerbed[position] == 1) {
			System.out.println("Return false becuase flower is there");
			return false;
		}
		if ((position - 1) != -1 && flowerbed[position - 1] == 1) {
			System.out.println("Return false becuase adjacent");
			return false;
		}
		if ((position + 1) != flowerbed.length && flowerbed[position + 1] == 1) {
			System.out.println("Return false becuase adjacent");
			return false;
		}
		System.out.println("Returning true");
		return true;
	}

	public boolean canPlaceFlowers(int[] flowerbed, int n) {
		int counter = 0;
		System.out.println("The array of flower bed is:");
		for (int i = 0; i < flowerbed.length; i++)
			System.out.print(flowerbed[i] + " ");
		if (n > flowerbed.length)
			return false;
		for (int i = 0; i < flowerbed.length; i++)
			if (canPlaceFlowerHere(flowerbed, i)) {
				flowerbed[i] = 1;
				counter++;
			}
		return counter >= n;
	}

	public static void main(String args[]) {
		int flowerbed[] = { 1, 0, 0, 0, 1 };
		int flowers = 1;
		LC0605CanPlaceFlowers solution = new LC0605CanPlaceFlowers();
		System.out.println(solution.canPlaceFlowers(flowerbed, flowers) + " is the final answer");
	}
}
