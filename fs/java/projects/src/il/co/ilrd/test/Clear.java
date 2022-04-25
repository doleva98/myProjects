package il.co.ilrd.test;

import java.util.Arrays;

interface s {
    default public void f() {
        System.out.println("hello");
    }
}

abstract class A implements s {

    public void c() {
        f();
    }
}

class B extends A implements s {
    public B() {
        super.c();
    }

    @Override
    public void f() {
        System.out.println("a");
    }
}

class Main {

    public static void main(String[] args) {
        B b = new B();
        /*  b.f();
        A a = new A(); */
    }
}