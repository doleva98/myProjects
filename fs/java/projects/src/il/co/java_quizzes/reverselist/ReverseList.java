package il.co.java_quizzes.reverselist;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ReverseList {
    public static <T> void revlist(List<T> list) {
        if (list == null || list.size() <= 1) {
            return;
        }
        T val = list.remove(0);
        revlist(list);
        list.add(val);
    }


    public static void main(String[] args) {
        List<String> gfg = new ArrayList<>(
                Arrays.asList("PLATFORM", "LEARNING", "BEST", "THE", "IS", "GFG"));

        revlist(gfg);

        System.out.println(gfg);
    }
}

