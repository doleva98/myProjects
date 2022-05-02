package il.co.java_quizzes.countPairsToSum;

import java.util.HashMap;
import java.util.Map;

public class CountPairsToSum {
    public static int countPairsToSum(int[] array, int targetSum) {
        // returns the number of pairs in the array that sum-up to targetSum.
        // Time complexity 0(n)
        int res = 0;
        Map<Integer, Integer> m = new HashMap<>();
        for (int number : array) {
            if (m.get(targetSum - number) != null) {
                res += m.get(targetSum - number);
            }
            if (m.get(number) == null) {
                m.put(number, 1);
            } else {
                m.put(number, m.get(number) + 1);
            }
        }
        return res;
    }

    public static void main(String[] args) {
        int[] a = new int[] { 1, 5, 7, -1, 5, 1, 6 };
        System.out.println(countPairsToSum(a, 6));
    }
}
