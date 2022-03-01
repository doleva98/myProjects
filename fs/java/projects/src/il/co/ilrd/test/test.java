package il.co.ilrd.test;

import java.util.HashMap;
import java.util.Map;

class Foo {
    public static void main(String[] args) {
        // Creating an empty HashMap
        Map<Integer, String> hash_map = new HashMap<>();

        // Mapping string values to int keys
        hash_map.put(10, "Geeks");
        hash_map.put(15, "4");
        hash_map.put(20, "Geeks");
        hash_map.put(25, "Welcomes");
        hash_map.put(30, "You");

        System.out.println(hash_map);
        System.out.println(hash_map.entrySet());

    }

}