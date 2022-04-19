package il.co.java_quizzes.LRUCache;

import java.util.LinkedHashMap;

public class LRUCache<K, V> {
    private final LinkedHashMap<K, V> linkedHashMap;
    private int size = 0;
    private final int maxCapacity;

    public LRUCache(int maxCapacity) {
        linkedHashMap = new LinkedHashMap<>(maxCapacity, 1);
        this.maxCapacity = maxCapacity;
    }

    public void put(K key, V value) {
        if (size >= maxCapacity) {
            linkedHashMap.remove(linkedHashMap.keySet().stream().findFirst().get());
        } else {
            ++size;
        }
        linkedHashMap.put(key, value);
    }

    public V get(K key) {
        V val = linkedHashMap.get(key);
        linkedHashMap.remove(key);
        linkedHashMap.put(key, val);
        return val;
    }

}
