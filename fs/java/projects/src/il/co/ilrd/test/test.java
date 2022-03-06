package il.co.ilrd.test;

import java.io.StringReader;
import java.security.KeyStore.Entry;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Vector;

import javax.sound.sampled.SourceDataLine;

class Test<T extends Comparable<T>> {
    public static void main(String[] args) {
        int[] a = new int[] { 3, 5, 16, 50 };
        for (Integer i : foo(a, 53)) {
            System.out.println(i);
        }

    }

    public static List<Integer> foo(int[] a, int num) {
        List<Integer> l = new ArrayList<>();
        for (int i = a.length - 1; i >= 0; --i) {
            if (a[i] == num) {
                l.add(a[i]);
                return l;
            } else if (a[i] < num) {
                l.add(a[i]);
                num -= a[i];
            }
        }
        return null;
    }

}

@Override
    public boolean containsKey(Object key) {
        int index = key.hashCode() % table.size();

        List<Entry<K,V>> curr_list = table.get(index);
        for(Entry<K,V> pair : curr_list)
        {
            if(pair.getKey().equals(key))
            {
                return true;
            }
        }
        return false;

    }

    @Override
    public V put(K key, V value) {
        V value_ret = get(key); 
        if(value_ret != null) 
        {
            remove(key
        }
        int index = key.hashCode() % table.size();

        List<Entry<K,V>> curr_list = table.get(index);
        curr_list.add(Pair.of(key,value));
    }
    