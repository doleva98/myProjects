package il.co.ilrd.test;

import java.util.ArrayList;
import java.util.List;

class Test {
    public static void main(String[] args) {
        List<Integer> l = new ArrayList<>();
        l.add(4);
        l.add(543);
        l.remove(0);
        System.out.println(l.get(0));
    }
}
