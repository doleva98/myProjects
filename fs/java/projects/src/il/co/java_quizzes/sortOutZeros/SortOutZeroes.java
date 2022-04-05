package il.co.java_quizzes.sortOutZeros;

import java.util.Arrays;

class SortOutZeroesClass {
    public static int[] SortOutZeroes(int[] a) {
        int countZeroes = 0;
        for (int i = 0; i < a.length; ++i) {
            if (a[i] == 0) {
                ++countZeroes;
            } else {
                int temp = a[i];
                a[i] = a[i - countZeroes];
                a[i - countZeroes] = temp;
            }
        }
        return a;
    }

    public static void main(String[] args) {
        int[] a = { 0, 3, 1, 4, 0, 0, 4, 0, 32, 0 };
        System.out.println(Arrays.toString(SortOutZeroes(a)));
    }
}
