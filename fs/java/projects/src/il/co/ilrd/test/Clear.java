package il.co.ilrd.test;

class Outer {
    // static int x;

    private class Inner {

        public void foo1() {
            System.out.println(Nested.x);
        }
    }

    private static class Nested {
        static int x = 5;

        public void foo1() {
            Inner i = new Outer().new Inner();

        }
    }

    void foo() {
        class Local {

            public void foo1() {
                Inner i = new Outer().new Inner();

            }
        }

        Local l = new Local();

    }

    public static void main(String[] args) {
        Outer o = new Outer();
        Inner i = new Outer().new Inner();
        i.foo1();

    }
}
