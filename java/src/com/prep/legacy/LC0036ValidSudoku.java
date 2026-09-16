package com.prep.legacy;

import java.util.*;

public class LC0036ValidSudoku {
	private boolean master_debug = false;

	public boolean isValidSudoku(char[][] board) {
		boolean fullValidate = false;
		for (int x = 0; x < board.length; x++)
			for (int y = 0; y < board.length; y++)
				fullValidate = fullValidate | validateJunction(x, y, board);
		fullValidate = fullValidate | upTo9inSubSquare(board);
		return !fullValidate;
	}

	public boolean upTo9inSubSquare(char board[][]) {
		boolean result = false;
		for (int x = 0; x < board.length; x++)
			for (int y = 0; y < board.length; y++)
				if (x % 3 == 0 && y % 3 == 0)
					result = result | validateSubSquares(x, y, board);
		return result;
	}

	private boolean validateSubSquares(int x, int y, char board[][]) {
		boolean result = false;
		HashSet<Integer> numberSet = new HashSet<Integer>(9);
		for (int xc = 0; xc < 3; xc++)
			for (int yd = 0; yd < 3; yd++) {
				if (board[xc][yd] == '.')
					continue;
				if (numberSet.contains(getIntegerFromCharacter(board[xc][yd])))
					result = result | true;
				else
					numberSet.add(getIntegerFromCharacter(board[xc][yd]));
			}
		return result;
	}

	public boolean validateJunction(int x, int y, char[][] board) {
		boolean result = false;
		if (master_debug)
			System.out.println("\nValidating the junction of " + x + ", " + y);
		result = validateRow(x, board);
		result = result | validateColumn(y, board);
		return result;
	}

	private boolean validateRow(int x, char[][] board) {
		boolean rowValidation = false;
		if (master_debug)
			System.out.println("\nValidating the row " + (x + 1));
		HashSet<Integer> numberSet = new HashSet<Integer>(0);
		char row[] = board[x];
		for (int i = 0; i < row.length; i++) {
			if (row[i] == '.')
				continue;
			if (validateCell(row[i]))
				rowValidation = rowValidation | true;
			if (numberSet.contains(getIntegerFromCharacter(row[i])))
				rowValidation = rowValidation | true;
			else
				numberSet.add(getIntegerFromCharacter(row[i]));
		}
		return rowValidation;
	}

	private boolean validateColumn(int x, char[][] board) {
		boolean colValidation = false;
		if (master_debug)
			System.out.println("\nValidating the column " + (x + 1));
		HashSet<Integer> numberSet = new HashSet<Integer>(10);
		char col[] = new char[9];
		for (int i = 0; i < board.length; i++) {
			col[i] = board[i][x];
			if (master_debug)
				System.out.print(col[i] + " ");
		}
		for (int i = 0; i < col.length; i++) {
			if (col[i] == '.')
				continue;
			if (validateCell(col[i]))
				colValidation = colValidation | true;
			if (numberSet.contains(getIntegerFromCharacter(col[i])))
				colValidation = colValidation | true;
			else
				numberSet.add(getIntegerFromCharacter(col[i]));
		}
		return colValidation;
	}

	public boolean validateCell(char ch) {
		return getIntegerFromCharacter(ch) < 1 || getIntegerFromCharacter(ch) > 9;
	}

	private Integer getIntegerFromCharacter(char c) {
		return Integer.valueOf(c - '0');
	}

	public int minimumTotal(List<List<Integer>> triangle) {
		Integer sum = 0;
		Integer prevIndex = 0;
		for (int i = 0; i < triangle.size(); i++) {
			List<Integer> innerArrayList = triangle.get(i);
			Integer current_iter_min_amount = Integer.MAX_VALUE;
			for (int j = 0; j < innerArrayList.size(); j++)
				if (innerArrayList.get(j) < current_iter_min_amount && isAdjacent(j, prevIndex)) {
					current_iter_min_amount = innerArrayList.get(j);
					if (master_debug)
						System.out.println("Selected " + current_iter_min_amount + " at level " + (i + 1));
					prevIndex = j;
				}
			sum = sum + current_iter_min_amount;
		}
		return sum;
	}

	private boolean isAdjacent(Integer j, Integer prevIndex) {
		return prevIndex == j || prevIndex == (j - 1);
	}

	public static void main(String args[]) {
		LC0036ValidSudoku solution = new LC0036ValidSudoku();
		char board[][] = { { '5', '3', '.', '.', '7', '.', '.', '.', '.' },
				{ '6', '.', '.', '1', '9', '5', '.', '.', '.' }, { '.', '9', '8', '.', '.', '.', '.', '6', '.' },
				{ '8', '.', '.', '.', '6', '.', '.', '.', '3' }, { '4', '.', '.', '8', '.', '3', '.', '.', '1' },
				{ '7', '.', '.', '.', '2', '.', '.', '.', '6' }, { '.', '6', '.', '.', '.', '.', '2', '8', '.' },
				{ '.', '.', '.', '4', '1', '9', '.', '.', '5' }, { '.', '.', '.', '.', '8', '.', '.', '7', '9' } };
		System.out.println(solution.isValidSudoku(board));
	}
}
