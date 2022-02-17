package il.co.java_quizzes.findThief;
class findThief {
    public static void main(String args[]) {
        int val[] = { 10, 40, 30, 50 };
        int wt[] = { 5, 4, 6, 3 };
        System.out.println(String.format("%d", MaxStolenVal(val, wt, val.length, 10)));

    }

    static int Max(int a, int b) {
        return a > b ? a : b;
    }

    public static int MaxStolenVal(int val[], int wt[], int N, int max_w) {
        if (0 == N || 0 == max_w) {
            return 0;
        }

        if (wt[N - 1] > max_w) {
            return MaxStolenVal(val, wt, N - 1, max_w);
        } else {
            return Max(val[N - 1] + MaxStolenVal(val, wt, N - 1, max_w - wt[N - 1]),
                    MaxStolenVal(val, wt, N - 1, max_w));
        }
    }
}

