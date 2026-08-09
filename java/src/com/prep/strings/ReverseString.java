package com.prep.strings;

/**
 * LeetCode 344 - Reverse String.
 * Two-pointer in-place swap. Time O(n), space O(1).
 */
public class ReverseString {

    public void reverseString(char[] s) {
        int left = 0, right = s.length - 1;
        while (left < right) {
            char tmp = s[left];
            s[left] = s[right];
            s[right] = tmp;
            left++;
            right--;
        }
    }

    public static void main(String[] args) {
        ReverseString sol = new ReverseString();
        char[] input = {'h', 'e', 'l', 'l', 'o'};
        sol.reverseString(input);
        System.out.println(new String(input)); // olleh
    }
}
