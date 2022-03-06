package il.co.ilrd.hashmap;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Collection;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.Set;
import java.util.Map.Entry;
import org.junit.Before;
import org.junit.Test;

public class HashmapTest {

    Hashmap<Integer, Integer> hm;

    @Before
    public void before() {
        hm = new Hashmap<>();
    }

    @Test
    public void testEntrySet() {
        int numTest = 80;
        for (int i = 0; i < numTest; ++i) {
            hm.put(Integer.valueOf(i), Integer.valueOf(i));
        }
        Set<Entry<Integer, Integer>> entrySet = hm.entrySet();
        assertEquals(entrySet.size(), hm.size());

        for (int i = 0; i < numTest; ++i) {
            assertTrue(entrySet.contains(Pair.of(i, i)));
        }

    }

    @Test
    public void testKeySet() {
        int numTest = 80;
        for (int i = 0; i < numTest; ++i) {
            hm.put(Integer.valueOf(i), Integer.valueOf(i));
        }
        Set<Integer> keySet = hm.keySet();

        for (int i = 0; i < numTest; ++i) {
            assertTrue(keySet.contains(i));
        }

        assertEquals(keySet.size(), hm.size());

        Collection<Integer> valueSet = hm.values();
        assertEquals(valueSet.size(), hm.size());

        for (Integer key : keySet) {
            valueSet.contains(hm.get(key));
        }
    }

    @Test
    public void testAll() {
        assertTrue(hm.isEmpty());
        int numTest = 80;
        for (int i = 0; i < numTest; ++i) {
            hm.put(Integer.valueOf(i), Integer.valueOf(i));
            assertEquals(hm.size(), i + 1);
            assertEquals(hm.get(i), i);
            assertTrue(hm.containsKey(i));
            assertTrue(hm.containsValue(i));
        }
        for (int i = numTest; i < numTest * 2; ++i) {
            assertFalse(hm.containsKey(i));
            assertFalse(hm.containsValue(i));
        }
        assertFalse(hm.isEmpty());
        hm.clear();
        assertTrue(hm.isEmpty());
        assertEquals(hm.size(), 0);
        for (int i = 0; i < numTest; ++i) {
            assertFalse(hm.containsKey(i));
            assertFalse(hm.containsValue(i));
            System.out.println(i);
        }
    }

    @Test
    public void testPutAll() {
        int numTest = 80;
        int moreNum = numTest * 2;
        Hashmap<Integer, Integer> hm1 = new Hashmap<>(moreNum);
        for (int i = 0; i < numTest; ++i) {
            hm.put(Integer.valueOf(i), Integer.valueOf(i));
            hm1.put(Integer.valueOf(i), Integer.valueOf(i));
        }

        assertEquals(hm1.size(), hm.size());

        for (int i = numTest; i < moreNum; ++i) {
            hm1.put(Integer.valueOf(i), Integer.valueOf(i));
        }
        hm.putAll(hm1);
        assertEquals(hm1.size(), hm.size());

        for (Integer key : hm1.keySet()) {
            assertTrue(hm.containsKey(key));
        }
    }

    @Test
    public void testRemove() {
        int numTest = 80;
        for (int i = 0; i < numTest; ++i) {
            hm.put(Integer.valueOf(i), Integer.valueOf(i));
        }
        for (int i = 0; i < numTest; ++i) {
            hm.remove(i);
            assertEquals(hm.get(i), null);
        }
        assertNull(hm.remove(153));
    }

    @Test
    public void testValues() {
        int numTest = 80;
        for (int i = 0; i < numTest; ++i) {
            hm.put(Integer.valueOf(i), Integer.valueOf(i));
        }
        Collection<Integer> valueSet = hm.values();

        for (int i = 0; i < numTest; ++i) {
            assertTrue(valueSet.contains(i));
        }
    }

    @Test(expected = ConcurrentModificationException.class)
    public void testModException() {
        int numTest = 80;
        for (int i = 0; i < numTest; ++i) {
            hm.put(Integer.valueOf(i), Integer.valueOf(i));
        }
        Set<Entry<Integer, Integer>> entry = hm.entrySet();

        Iterator<Entry<Integer, Integer>> iter = entry.iterator();

        for (int i = 0; i < numTest / 2; ++i) {
            iter.next();
        }
        hm.put(numTest + 421, 45342);

        iter.next();

    }

    @Test
    public void testValues2() {
        int numTest = 80;
        for (int i = 0; i < numTest; ++i) {
            hm.put(Integer.valueOf(i), Integer.valueOf(0));
        }
        Collection<Integer> valueSet = hm.values();
        assertEquals(valueSet.size(), 80);
    }

}
