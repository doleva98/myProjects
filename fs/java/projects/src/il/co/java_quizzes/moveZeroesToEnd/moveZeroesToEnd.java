package il.co.java_quizzes.moveZeroesToEnd;

class moveZeroesToEnd {
    public static void main(String[] args) {
        int[] a = { 1, 4, 0, 656, 0, 0, 54545 };
        PushZeroesToEnd(a);
        for(int i : a)
        {
            System.out.println(i);
        }
    }

    public static void PushZeroesToEnd(int[] arr) {
        int non_zeroes_counter = 0;
        for (int i = 0; i < arr.length; ++i) {
            if (arr[i] != 0) {
                arr[non_zeroes_counter++] = arr[i];
            }
        }

        while (non_zeroes_counter < arr.length) {
            arr[non_zeroes_counter++] = 0;
        }

    }
}