package il.co.ilrd.test;

class test {
    public static void main(String[] args) {
        hi d = new hi();
        hi.inner i = d.new inner();
        i.m();
    }
}

class hi {
    int x = 0;

    private void foo() {
        System.out.println("hello");
    }

    class inner {
        public int x = 1;
        /* public void foo(int x)
        {
            System.out.println(x);
        } */

        public void m() {
            foo();
        }
    }
}
