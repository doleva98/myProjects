package il.co.ilrd.collectionsws;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class CollectionWs {
    public static void main(String[] args) {
        int[] a = new int[] { 1, 4, 6, 34, 2, 53 };
        System.out.println(Arrays.toString(a));
        List<Integer> list = new ArrayList<>();
        for (int i : a) {
            list.add(i);
        }
        Collections.sort(list);
        System.out.println(list);

        Map<String, Integer> map = new HashMap<>();
        map.put("Sunday", 1);
        map.put("Monday", 2);
        map.put("Tuseday", 3);
        map.put("Wendsday", 4);
        map.put("thursday", 5);
        map.put("Friday", 6);
        map.put("Saturday", 7);

        for (Map.Entry<String, Integer> i : map.entrySet()) {
            System.out.println(i);
        }
        for (Integer i : map.values()) {
            System.out.println(i);
        }

        DataObject[] a2 = new DataObject[6];
        a2[0] = new DataObject("fdfdf", 4);
        a2[1] = new DataObject("fds", 5);
        a2[2] = new DataObject("fgdfgdfdfdf", 0);
        a2[3] = new DataObject("fds", 15);
        a2[4] = new DataObject("fds", 8);
        a2[5] = new DataObject("fgdfgdfdfdf", 34);

        Map<String, Integer> m2 = new HashMap<>();
        for (DataObject data : a2) {
            String code = data.getCode();
            int value = m2.containsKey(code) ? m2.get(code) + data.getValue() : data.getValue();
            m2.put(code, value);
        }
        System.out.println(m2);
    }
}

class DataObject {
    private String code;
    private int value;

    public DataObject(String code, int value) {
        this.code = code;
        this.value = value;
    }

    public String getCode() {
        return this.code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public int getValue() {
        return this.value;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
