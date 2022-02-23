package il.co.ilrd.test;

import java.util.Scanner;

class Foo {
    public static void main(String[] args) {
        try {
            foo();
        } catch (ArithmeticException e) {
            System.out.println("sdsds");
        }
    }

    public static void foo() throws IllegalArgumentException, ArithmeticException {
        try (Scanner scan = new Scanner(System.in)) {
            throw new IllegalArgumentException();
        } finally {
            throw new ArithmeticException();

        }
    }
}