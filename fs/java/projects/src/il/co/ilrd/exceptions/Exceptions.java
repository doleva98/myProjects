package il.co.ilrd.exceptions;

import java.io.IOException;

class Foo {
    public static void func1() throws IOException {
        /* throw new IOException(); */
    }

    public static void func2() {
        throw new NullPointerException();
    }

    public static void func3() {
        throw new MyException1();
    }

    public static void func4() throws MyException2 {
        throw new MyException2();
    }

    public static void main(String[] args) {
        /*         func2();
        
        try {
            func1();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } */

        func3();

        try {
            func4();
        } catch (MyException2 e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        byte[] array = new byte[100];
        byte t = array[101];
    }
}

class MyException1 extends RuntimeException {

}

class MyException2 extends IOException {

}
