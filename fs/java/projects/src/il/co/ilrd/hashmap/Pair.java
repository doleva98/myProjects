/* roy CR */
package il.co.ilrd.hashmap;

import java.util.Comparator;
import java.util.Map;

public class Pair<K, V> implements Map.Entry<K, V> {
    private K key;
    private V value;

    private Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    public static <K, V> Pair<K, V> of(K key, V value) {
        return new Pair<>(key, value);
    }

    public static <K, V> Pair<V, K> swap(Pair<K, V> pair) {
        return new Pair<>(pair.getValue(), pair.getKey());
    }

    @Override
    public K getKey() {
        return key;
    }

    public K setKey(K key) {
        K old_key = this.key;
        this.key = key;
        return old_key;
    }

    @Override
    public V getValue() {
        return value;
    }

    @Override
    public V setValue(V value) {
        V old_value = this.value;
        this.value = value;
        return old_value;
    }

    public static <T extends Comparable<T>> Pair<T, T> minMax(T[] array) {
        return minMax(array, (o1, o2) -> o1.compareTo(o2));
        /* 
        
        Pair<T, T> pair = new Pair<>(array[0], array[0]);
        int i = 1;
        
        if (array.length % 2 == 0) {
            if (array[0].compareTo(array[1]) < 0) {
                pair.setValue(array[1]);
            } else {
                pair.setKey(array[1]);
            }
            i = 2;
        }
        while (i < array.length - 1) {
            if (array[i].compareTo(array[i + 1]) < 0) {
                if (array[i].compareTo(pair.getKey()) < 0) {
                    pair.setKey(array[i]);
                }
                if (array[i + 1].compareTo(pair.getValue()) > 0) {
                    pair.setValue(array[i + 1]);
                }
            } else {
                if (array[i + 1].compareTo(pair.getKey()) < 0) {
                    pair.setKey(array[i + 1]);
                }
                if (array[i].compareTo(pair.getValue()) > 0) {
                    pair.setValue(array[i]);
                }
            }
            i += 2;
        }
        return pair; */
    }/* create new Pair */

    public static <T> Pair<T, T> minMax(T[] array, Comparator<T> comp) {

        Pair<T, T> pair = new Pair<>(array[0], array[0]);
        int i = 1;

        if (array.length % 2 == 0) {
            if (comp.compare(array[0], array[1]) < 0) {
                pair.setValue(array[1]);
            } else {
                pair.setKey(array[1]);
            }
            i = 2;
        }
        while (i < array.length - 1) {
            if (comp.compare(array[i], array[i + 1]) < 0) {
                if (comp.compare(array[i], pair.getKey()) < 0) {
                    pair.setKey(array[i]);
                }
                if (comp.compare(array[i + 1], pair.getValue()) > 0) {
                    pair.setValue(array[i + 1]);
                }
            } else {
                if (comp.compare(array[i + 1], pair.getKey()) < 0) {
                    pair.setKey(array[i + 1]);
                }
                if (comp.compare(array[i], pair.getValue()) > 0) {
                    pair.setValue(array[i]);
                }
            }
            i += 2;
        }
        return pair;
    }

    @Override
    public int hashCode() {
        return value.hashCode() ^ key.hashCode();
    }

    @Override
    public boolean equals(Object o) {
        if (!(o instanceof Pair)) {
            return false;
        }

        @SuppressWarnings("unchecked")
        Pair<K, V> pair = (Pair<K, V>) o;
        return key.equals(pair.key) && value.equals(pair.value);
    }

    @Override
    public String toString() {
        return "(" + key + "," + value + ")";
    }

}
