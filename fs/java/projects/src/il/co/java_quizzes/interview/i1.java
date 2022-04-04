package il.co.java_quizzes.interview;

public class i1 {
    /* string, is unique */
    public static boolean isUnique(String str) {
        long longCharInStr = 0;

        for (int i = 0; i < str.length(); ++i) {
            if (((longCharInStr >> (str.charAt(i) - 'A')) & 1) == 1) {
                return false;
            }
            longCharInStr |= (1 << (str.charAt(i) - 'A'));
        }
        return true;
    }

    public static void main(String[] args) {
        System.out.println(isUnique("AB"));
        System.out.println(isUnique("dsdlksldks"));
    }
}
