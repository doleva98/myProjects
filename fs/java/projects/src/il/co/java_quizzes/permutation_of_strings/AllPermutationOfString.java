package il.co.java_quizzes.permutation_of_strings;

public class AllPermutationOfString {
    public static void printPermutationOfAString(String str) {
        printPermutationOfAStringHelper(str, "");
    }

    private static void printPermutationOfAStringHelper(String str, String ans) {
        if (0 == str.length()) {
            System.out.println(ans + " ");
            return;
        }

        for (int i = 0; i < str.length(); ++i) {

            String ros = str.substring(0, i) + str.substring(i + 1);

            printPermutationOfAStringHelper(ros, ans + str.charAt(i));
        }
    }
    public static void main(String[] args) {
        printPermutationOfAString("abb");
    }
}
