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
import java.util.Set;

class Hashmap<K, V> implements Map<K, V> {

    private List<List<Entry<K, V>>> list;
    private int versionNum;

    public Hashmap() {
        this(16);
    }

    public Hashmap(int capacity) {
        list = new ArrayList<>(capacity);
        versionNum = 0;

        /* eager */
        for (int i = 0; i < capacity; ++i) {
            list.add(new LinkedList<>());
        }
    }

    @Override
    public void clear() {
        newVersion();
        for (List<Entry<K, V>> l : list) {
            l.clear();
        }
    }

    @Override
    public boolean containsKey(Object key) {
        int index = key.hashCode() % list.size();
        if (list.get(index) == null) {
            return false;
        }
        for (Entry<K, V> p : list.get(index)) {
            if (p.getKey().equals(key)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean containsValue(Object value) {
        for (List<Entry<K, V>> curr_list : list) {
            for (Entry<K, V> p : curr_list) {
                if (p.getValue().equals(value)) {
                    return true;
                }
            }
        }
        return false;
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        return new SetOfPairs();
    }

    private class SetOfPairs extends AbstractSet<Entry<K, V>> {

        @Override
        public Iterator<Entry<K, V>> iterator() {
            Iterator<List<Entry<K, V>>> outerIter = list.iterator();

            return new SetOfPairsIterator(outerIter.next().iterator(), outerIter);

        }

        @Override
        public int size() {
            return list.size();
        }

        private class SetOfPairsIterator implements Iterator<Entry<K, V>> {
            private Iterator<Entry<K, V>> innerIter;
            private Iterator<List<Entry<K, V>>> outerIter;
            private final int VERSIONNUMITERATOR;

            public SetOfPairsIterator(Iterator<Entry<K, V>> innerIter,
                    Iterator<List<Entry<K, V>>> outerIter) {
                this.innerIter = innerIter;
                this.outerIter = outerIter;
                VERSIONNUMITERATOR = versionNum;
            }

            @Override
            public boolean hasNext() {

                return innerIter.hasNext() || outerIter.hasNext();
            }

            @Override
            public Entry<K, V> next() {
                if (VERSIONNUMITERATOR != versionNum) {
                    throw new ConcurrentModificationException();
                }
                if (!innerIter.hasNext()) {/* current list is over, need to change to next list */
                    innerIter = outerIter.next().iterator();
                }
                return innerIter.next();
            }
        }

    }

    @Override
    public V get(Object key) {
        int index = key.hashCode() % list.size();
        for (Entry<K, V> p : list.get(index)) {
            if (p.getKey().equals(key)) {
                return p.getValue();
            }
        }
        return null;
    }

    @Override
    public boolean isEmpty() {
        for (List<Entry<K, V>> l : list) {
            if (!l.isEmpty()) {
                return false;
            }
        }
        return true;
    }

    @Override
    public Set<K> keySet() {
        return new SetOfKeys();
    }

    private class SetOfKeys extends AbstractSet<K> {

        @Override
        public Iterator<K> iterator() {
            Iterator<List<Entry<K, V>>> outerIter = list.iterator();

            return new SetOfKeysIterator(outerIter.next().iterator(), outerIter);

        }

        @Override
        public int size() {
            return list.size();
        }

        private class SetOfKeysIterator implements Iterator<K> {
            private Iterator<Entry<K, V>> innerIter;
            private Iterator<List<Entry<K, V>>> outerIter;
            private final int VERSIONNUMITERATOR;

            public SetOfKeysIterator(Iterator<Entry<K, V>> innerIter,
                    Iterator<List<Entry<K, V>>> outerIter) {
                this.innerIter = innerIter;
                this.outerIter = outerIter;
                VERSIONNUMITERATOR = versionNum;
            }

            @Override
            public boolean hasNext() {

                return innerIter.hasNext() || outerIter.hasNext();
            }

            @Override
            public K next() {
                if (VERSIONNUMITERATOR != versionNum) {
                    throw new ConcurrentModificationException();
                }
                if (!innerIter.hasNext()) {/* current list is over, need to change to next list */
                    innerIter = outerIter.next().iterator();
                }
                return innerIter.next().getKey();
            }
        }

    }

    @Override
    public V put(K key, V value) {
        newVersion();
        V old_value = null;
        if (containsKey(key)) {
            old_value = this.get(key);
            remove(key);
        }
        int index = key.hashCode() % list.size();
        list.get(index).add(Pair.of(key, value));
        return old_value;
    }

    @Override
    public void putAll(Map<? extends K, ? extends V> m) {
        newVersion();
        // TODO Auto-generated method stub

    }

    @Override
    public V remove(Object key) {
        newVersion();
        int index = key.hashCode() % list.size();
        for (Entry<K, V> p : list.get(index)) {
            if (p.getKey().equals(key)) {
                return p.getValue();
            }
        }
        return null;
    }

    @Override
    public int size() {
        int counter = 0;
        for (int i = 0; i < list.size(); ++i) {
            counter += list.get(i).size();
        }
        return counter;
    }

    @Override
    public Collection<V> values() {
        return new CollectionOfValues();
    }

    private class CollectionOfValues extends AbstractCollection<V> {

        @Override
        public Iterator<V> iterator() {
            Iterator<List<Entry<K, V>>> outerIter = list.iterator();

            return new CollectionOfValuesIterator(outerIter.next().iterator(), outerIter);

        }

        @Override
        public int size() {
            return list.size();
        }

        private class CollectionOfValuesIterator implements Iterator<V> {
            private Iterator<Entry<K, V>> innerIter;
            private Iterator<List<Entry<K, V>>> outerIter;
            private final int VERSIONNUMITERATOR;

            public CollectionOfValuesIterator(Iterator<Entry<K, V>> innerIter,
                    Iterator<List<Entry<K, V>>> outerIter) {
                this.innerIter = innerIter;
                this.outerIter = outerIter;
                VERSIONNUMITERATOR = versionNum;
            }

            @Override
            public boolean hasNext() {

                return innerIter.hasNext() || outerIter.hasNext();
            }

            @Override
            public V next() {
                if (VERSIONNUMITERATOR != versionNum) {
                    throw new ConcurrentModificationException();
                }
                if (!innerIter.hasNext()) {/* current list is over, need to change to next list */
                    innerIter = outerIter.next().iterator();
                }
                return innerIter.next().getValue();
            }
        }

    }

    private void newVersion() {
        if (versionNum == Integer.MAX_VALUE) {
            versionNum = 0;
        }
        ++versionNum;
    }

}
