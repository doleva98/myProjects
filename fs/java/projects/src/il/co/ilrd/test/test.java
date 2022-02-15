package test;

class test {

    public static void main(String[] args) {
        Outer o = new Outer();
        Outer.Inner i = o.new Inner();
        i.foo();
    }
}

class Outer {
    private int x;

    Outer() {
        this.x = 3;
    }

    public void f() {
        System.out.println(x);
    }

    class Inner {
        private int x;

        public Inner() {
            System.out.println(x);
        }

        public void foo() {
        }
    }
}