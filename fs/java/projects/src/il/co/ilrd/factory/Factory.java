package il.co.ilrd.factory;

import java.util.HashMap;
import java.util.Map;

interface Animal {

}

public class Factory<K, V> {
    Map<K, Class<?>> hm = new HashMap<>();

    public void add(K key, Class<?> ctor) {
        hm.put(key, ctor);
    }

    public Object create(K key) {
        return hm.get(key);
    }

    public void create(K key, V additionalData) {

    }

}
