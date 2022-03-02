package il.co.ilrd.test;

import java.io.StringReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.sound.sampled.SourceDataLine;

class Test {
    public static void main(String[] args) {
        System.out.println();
        List<Object> mainList = new ArrayList<>();
        List rawList = new ArrayList();

        List<Integer> intList = new ArrayList<>();
        intList.add(6432);
        mainList.addAll(intList);
        rawList.addAll(intList);

        List<String> strList = new ArrayList<>();
        
        strList.addAll(rawList);

        strList.addAll(mainList);

    }

    public static int count(Set<?> s1, Set<?> s2) {
        int res = 0;
        for (Object o : s1) {
            if (s2.contains(o)) {
                ++res;
            }
        }
        s1.add("Dumbelroe");
        s2.add(23);
        return res;
    }

}

class Dog<T> {
    public void sound() {
        System.out.println("WOOF");
    }
}