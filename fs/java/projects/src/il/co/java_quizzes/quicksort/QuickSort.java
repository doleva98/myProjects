package il.co.java_quizzes.quicksort;

import java.util.Arrays;

public class QuickSort {
    public static int[] quickSort(int[] a) {
        quickSortHelper(a, 0, a.length - 1);
        return a;
    }

    private static int[] quickSortHelper(int[] a, int l, int r) {
        if (l < r) {
            int p = partition(a, l, r);
            quickSortHelper(a, l, p - 1);
            quickSortHelper(a, p + 1, r);
        }
        return a;
    }

    private static int partition(int[] a, int l, int r) {
        int pivot = a[r];
        int little_then_pivot = l - 1;
        for (int i = l; i < r; ++i) {
            if (a[i] < pivot) {
                System.out.println(Arrays.toString(a));
                int temp = a[++little_then_pivot];
                a[little_then_pivot] = a[i];
                a[i] = temp;
            }

        }

        int temp = a[++little_then_pivot];
        a[little_then_pivot] = a[r];
        a[r] = temp;
        return little_then_pivot;
    }

    public static void main(String[] args) {
        int[] a = new int[] { 2,1,9,8,7,6,5,4,3 };
        System.out.println(Arrays.toString(quickSort(a)));
    }
}
