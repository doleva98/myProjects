package il.co.ilrd.test;

import java.io.StringReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.sound.sampled.SourceDataLine;

class Test<T extends Comparable<T>> {
    public static void main(String[] args) {
        Test<String> t = new Test<>(String.valueOf(4));
        System.out.println(t.de.getClass().getName());
        List<String> d = new ArrayList<>();

        foo(d);
    }

    public T de;

    public Test(T de) {
        this.de = de;
    }

    public void foo(List<Object> d) {

    }
}
