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

    private List<List<Pair<K, V>>> list;
    private int versionNum;

    public Hashmap() {
        this(16);
    }

    public Hashmap(int capacity) {
        list = new ArrayList<>(capacity);
    }

    @Override
    public void clear() {
        newVersion();
        for (int i = 0; i < size(); ++i) {
            list.get(i).clear();
        }
    }

    @Override
    public boolean containsKey(Object key) {
        int index = key.hashCode() % list.size();
        List<Pair<K, V>> curr_list = list.get(index);
        for (Pair<K, V> p : curr_list) {
            if (p.getKey().equals(key)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean containsValue(Object value) {
        for (int i = 0; i < size(); ++i) {
            List<Pair<K, V>> curr_list = list.get(i);
            for (Pair<K, V> p : curr_list) {
                if (p.getValue().equals(value)) {
                    return true;
                }
            }
        }

        return false;
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        Set<Entry<K, V>> = H
        return null;
    }

    private class SetOfPairs extends AbstractSet<Entry<K, V>> {

        @Override
        public Iterator<Entry<K, V>> iterator() {
            int i;
            for (i = 0; i < list.size(); ++i) {
                if (list.get(i) != null && !list.get(i).isEmpty()) {
                    break;
                }
            }
            return new SetOfPairsIterator(i);

        }

        @Override
        public int size() {
            return list.size();
        }

        private class SetOfPairsIterator implements Iterator<Entry<K, V>> {
            private int current_item_in_list;
            private int current_list;
            private final int VERSIONNUMITERATOR;

            public SetOfPairsIterator(int current_list) {
                this.current_list = current_list;
                current_item_in_list = 0;
                VERSIONNUMITERATOR = versionNum;
            }

            @Override
            public boolean hasNext() {

                while (current_item_in_list < list.get(current_list).size() && current_list > )
                    if (current_list >= list.size()) {
                        return false;
                    }
            }

            @Override
            public Entry<K, V> next() {
                if (VERSIONNUMITERATOR != versionNum) {
                    throw new ConcurrentModificationException();
                }
                Entry<K, V> val = pair;

            }

        }

    }

    @Override
    public V get(Object key) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public boolean isEmpty() {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public Set<K> keySet() {
        // TODO Auto-generated method stub
        return null;
    }

    private class SetOfKeys extends AbstractSet<K> {
        private List<List<Pair<K, V>>> list;

        @Override
        public Iterator<K> iterator() {
            // TODO Auto-generated method stub
            return null;
        }

        @Override
        public int size() {
            // TODO Auto-generated method stub
            return 0;
        }

        private class SetOfPairsIterator implements Iterator<K> {

            @Override
            public boolean hasNext() {
                // TODO Auto-generated method stub
                return false;
            }

            @Override
            public K next() {
                // TODO Auto-generated method stub
                return null;
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
        List<Pair<K, V>> curr_list = list.get(index);
        if (curr_list == null) {
            curr_list = new LinkedList<>();
        }
        curr_list.add(Pair.of(key, value));
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
        // TODO Auto-generated method stub
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
        Collection<V> collection 
    }

    private class CollectionOfValues extends AbstractCollection<V> {
        private List<List<Pair<K, V>>> list;

        @Override
        public Iterator<V> iterator() {
            // TODO Auto-generated method stub
            return null;
        }

        @Override
        public int size() {
            // TODO Auto-generated method stub
            return 0;
        }

        private class SetOfPairsIterator implements Iterator<V> {

            @Override
            public boolean hasNext() {
                // TODO Auto-generated method stub
                return false;
            }

            @Override
            public V next() {
                // TODO Auto-generated method stub
                return null;
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
