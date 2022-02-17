package il.co.java_quizzes.Reverse_Palindrome;

class Reverse_Palindrome {

    private static void printReverse(String org) {
        for (int i = 0; i < org.length(); ++i) {
            System.out.print(org.charAt(org.length() - 1 - i));
        }
        System.out.println();
    }

    private static boolean isPalindrome(String str) {
        for (int i = 0; i < str.length() / 2; ++i) {
            if (str.charAt(i) != str.charAt(str.length() - 1 - i)) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        printReverse("hello world");
        System.out.println(isPalindrome("112321"));
    }
}