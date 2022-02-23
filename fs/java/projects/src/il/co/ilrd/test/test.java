package il.co.ilrd.test;


class Foo {

    Foo() {

    }

    int x = 5;

    public static void main(String[] args) {
        Foo f = new Foo();
        System.out.println(f.x);
    }

    {
        System.out.println(x);
    }
}