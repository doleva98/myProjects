/* Naama code reviewd */
package il.co.ilrd.hashmap;

import java.util.AbstractCollection;
import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

class Hashmap<K, V> implements Map<K, V> {

    private List<List<Entry<K, V>>> table_of_buckets;
    private int versionNum;
    private Set<Entry<K, V>> tablePairSet;
    private Set<K> tableKeySet;
    private Collection<V> tableValueCollection;
    private static int DEFAULTCAPACITY = 16;

    public Hashmap() {
        this(DEFAULTCAPACITY);
    }

    public Hashmap(int capacity) {
        if (capacity < 0) {
            throw new IllegalArgumentException();
        }
        table_of_buckets = new ArrayList<>(capacity);
        versionNum = Integer.MIN_VALUE;

        /* eager */
        for (int i = 0; i < capacity; ++i) {
            table_of_buckets.add(new LinkedList<>());
        }
    }

    @Override
    public void clear() {
        newVersion();
        for (List<Entry<K, V>> l : table_of_buckets) {
            l.clear();
        }
    }

    @Override
    public boolean containsKey(Object key) {
        Objects.requireNonNull(key);

        int index = key.hashCode() % table_of_buckets.size();
        for (Entry<K, V> p : table_of_buckets.get(index)) {
            if (p.getKey().equals(key)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean containsValue(Object value) {
        Objects.requireNonNull(value);

        return values().contains(value);
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        if (tablePairSet == null) {
            tablePairSet = new SetOfPairs();
        }
        return tablePairSet;
    }

    @Override
    public V get(Object key) {
        Objects.requireNonNull(key);

        int index = key.hashCode() % table_of_buckets.size();
        for (Entry<K, V> p : table_of_buckets.get(index)) {
            if (p.getKey().equals(key)) {
                return p.getValue();
            }
        }
        return null;
    }

    @Override
    public boolean isEmpty() {
        for (List<Entry<K, V>> l : table_of_buckets) {
            if (!l.isEmpty()) {
                return false;
            }
        }
        return true;
    }

    @Override
    public Set<K> keySet() {
        if (tableKeySet == null) {
            tableKeySet = new SetOfKeys();
        }
        return tableKeySet;
    }

    @Override
    public V put(K key, V value) {
        Objects.requireNonNull(key);
        Objects.requireNonNull(value);

        newVersion();
        V old_value = null;
        if (containsKey(key)) {
            old_value = get(key);
            remove(key);
        }
        int index = key.hashCode() % table_of_buckets.size();
        table_of_buckets.get(index).add(Pair.of(key, value));
        return old_value;
    }

    @Override
    public void putAll(Map<? extends K, ? extends V> m) {
        Objects.requireNonNull(m);

        newVersion();

        for (Entry<? extends K, ? extends V> p : m.entrySet()) {
            put(p.getKey(), p.getValue());
        }

    }

    @Override
    public V remove(Object key) {
        Objects.requireNonNull(key);

        newVersion();
        V value = null;
        int index = key.hashCode() % table_of_buckets.size();
        for (Entry<K, V> p : table_of_buckets.get(index)) {
            if (p.getKey().equals(key)) {
                value = p.getValue();
                table_of_buckets.get(index).remove(p);
                break;
            }
        }
        return value;
    }

    @Override
    public int size() {
        int counter = 0;

        for (List<Entry<K, V>> l : table_of_buckets) {
            counter += l.size();
        }
        return counter;
    }

    @Override
    public Collection<V> values() {
        if (tableValueCollection == null) {
            tableValueCollection = new CollectionOfValues();
        }
        return tableValueCollection;
    }

    private class SetOfPairs extends AbstractSet<Entry<K, V>> {

        @Override
        public Iterator<Entry<K, V>> iterator() {
            Iterator<List<Entry<K, V>>> outerIter = table_of_buckets.iterator();

            return new SetOfPairsIterator(outerIter.next().iterator(), outerIter);

        }

        @Override
        public int size() {
            return Hashmap.this.size();
        }

        private class SetOfPairsIterator implements Iterator<Entry<K, V>> {
            private Iterator<Entry<K, V>> innerIter;
            private Iterator<List<Entry<K, V>>> outerIter;
            private final int VERSIONNUMITERATOR;

            private SetOfPairsIterator(Iterator<Entry<K, V>> innerIter,
                    Iterator<List<Entry<K, V>>> outerIter) {
                this.innerIter = innerIter;
                this.outerIter = outerIter;
                VERSIONNUMITERATOR = versionNum;
                findNextValid();
            }

            @Override
            public boolean hasNext() {

                return innerIter.hasNext();

            }

            @Override
            public Entry<K, V> next() {
                if (VERSIONNUMITERATOR != versionNum) {
                    throw new ConcurrentModificationException();
                }

                Entry<K, V> curr = innerIter.next();
                findNextValid();
                return curr;
            }

            private void findNextValid() {
                while (!innerIter.hasNext() && outerIter.hasNext()) {
                    innerIter = outerIter.next().iterator();
                }
            }
        }

    }

    private class SetOfKeys extends AbstractSet<K> {

        @Override
        public Iterator<K> iterator() {
            return new SetOfKeysIterator();

        }

        @Override
        public int size() {
            return Hashmap.this.size();
        }

        private class SetOfKeysIterator implements Iterator<K> {
            private Iterator<Entry<K, V>> innerIter;

            private SetOfKeysIterator() {
                innerIter = new SetOfPairs().iterator();
            }

            @Override
            public boolean hasNext() {

                return innerIter.hasNext();

            }

            @Override
            public K next() {
                return innerIter.next().getKey();
            }
        }

    }

    private class CollectionOfValues extends AbstractCollection<V> {

        @Override
        public Iterator<V> iterator() {
            return new CollectionOfValuesIterator();

        }

        @Override
        public int size() {
            return Hashmap.this.size();
        }

        private class CollectionOfValuesIterator implements Iterator<V> {
            private Iterator<Entry<K, V>> innerIter;

            private CollectionOfValuesIterator() {
                innerIter = new SetOfPairs().iterator();
            }

            @Override
            public boolean hasNext() {

                return innerIter.hasNext();

            }

            @Override
            public V next() {
                return innerIter.next().getValue();
            }
        }

    }

    private void newVersion() {
        if (versionNum == Integer.MAX_VALUE) {
            versionNum = Integer.MIN_VALUE;
        }
        ++versionNum;
    }

}
