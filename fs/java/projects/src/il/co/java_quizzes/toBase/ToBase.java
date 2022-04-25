package il.co.java_quizzes.toBase;

import java.util.Stack;

public class ToBase {
    public static String toBase(int a, int base) {
        Stack<Integer> stack = new Stack<Integer>();

        while (a != 0) {
            stack.push(a % base);
            a /= base;
        }
        String res = "";
        while (!stack.isEmpty()) {
            int d = stack.pop();
            if (d <= 9) {
                res += d;
            } else {
                res += (char) (d + 'A' - 10);
            }
        }
        return res;
    }

    public static void main(String[] args) {
        System.out.println(toBase(52, 4));
        System.out.println(toBase(8, 2));
        System.out.println(toBase(54465261, 16));
    }
}
