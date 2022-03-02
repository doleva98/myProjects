package il.co.ilrd.test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.Vector;

class Foo {
    public static void main(String[] args) {
        Map<Integer, Integer> m = new TreeMap<>();
        List<String> l = new Vector<>();
        Integer[] a = new Integer[] { 1, 5, 7, 33 };
        List<Integer> b = new ArrayList<>(Arrays.asList(a));
        List<Integer> p = Arrays.asList(a);
        int[] j = new int[] { 3, 5, 6 };
        System.out.println(p);
    }

    public static void foo(double a) {
    }

}