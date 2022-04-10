package il.co.java_quizzes.findFirstNonDuplicate;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
/* 
class Node<T> {
    private T data;
    private Node<T> next;

    public Node(T data, Node<T> next) {
        this.data = data;
        this.next = next;
    }

} */

public class findFirstNonDuplicate {

    Map<Long, Boolean> map = new HashMap<>();
    private List<Long> noDupList = new ArrayList<>();

    public void input(long N) {
        if (!map.containsKey(N)) {
            map.put(N, true);
            noDupList.add(N);
        } else {
            noDupList.remove(N);
        }
    }

    public long output() {
        if (!noDupList.isEmpty()) {
            return noDupList.get(0);
        }
        return 0;
    }

    public static void main(String[] args) {
        long[] input = { 1, 2, 3, 4, 1, 1, 2, 3, 5 };
        long[] output = new long[11];

        findFirstNonDuplicate sequence = new findFirstNonDuplicate();

        for (int i = 0; i < input.length; ++i) {
            sequence.input(input[i]);
            output[i] = sequence.output();
            System.out.print(output[i] + ", ");
        }
    }
}
