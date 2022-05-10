package il.co.java_quizzes.swapString;

import java.util.Stack;

public class SwapString {
    public static void swapString(String s) {
        Stack<Character> stack = new Stack<>();
        String[] arr = s.split(" ");
        for (String word : arr) {
            for (char c : word.toCharArray()) {
                stack.push(c);
            }
            while (!stack.isEmpty()) {
                System.out.print(stack.pop());
            }
            System.out.print(" ");
        }

    }

    public static void main(String[] args) {
        swapString("Hello ROy");
    }
}
