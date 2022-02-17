package il.co.ilrd.test;

class test {
    public static void main(String[] args) {
        hi d = new hi();
    }
}

class hi {
    public static int x = 0;

    static class inner {
        public int x = 1;
        public void foo(int x)
        {
            System.out.println(x);
        }
    }
}

