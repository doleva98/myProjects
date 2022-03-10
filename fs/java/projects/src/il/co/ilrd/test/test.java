package il.co.ilrd.test;

import java.io.IOException;
import java.util.Collections;

class Test {

    public static void main(String[] args) {
        foo(5);
    }

    public static int foo(int i) {
        synchronized (Test.class) {
            if (i == 0) {
                return 0;
            }
            i = foo(--i) + 1;
        }
        return i;
    }
}