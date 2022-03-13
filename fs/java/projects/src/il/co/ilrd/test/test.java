package il.co.ilrd.test;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

class Test {

    public static void main(String[] args) {

        List<Integer> l = new ArrayList<>(Arrays.asList(1, 4, 57, 3));
        l.forEach(num -> System.out.println(num));
    }

    public static void a(int... a) {
        System.out.println(a.length);
    }
}