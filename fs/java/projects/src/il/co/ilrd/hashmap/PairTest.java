package il.co.ilrd.hashmap;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

import java.util.Comparator;

import org.junit.Before;
import org.junit.Test;

public class PairTest {

    Pair<Integer, Integer> p1;
    Pair<Integer, Integer> p2;
    Pair<Integer, Integer> p3;

    @Before
    public void before() {
        p1 = Pair.of(5, 3);
        p2 = Pair.of(5, 3);
        p3 = Pair.of(15, 43);

    }

    @Test
    public void testEquals() {
        assertEquals(p1, p2);
        assertNotEquals(p1, p3);
    }

    @Test
    public void testGetKey() {
        assertEquals(p1.getKey(), 5);
    }

    @Test
    public void testGetValue() {
        assertEquals(p1.getValue(), 3);

    }

    @Test
    public void testHashCode() {
        assertEquals(p2.hashCode(), p2.getKey().hashCode() ^ p2.getValue().hashCode());
    }

    @Test
    public void testMinMax() {
        Integer[] array = new Integer[] { 77, 3, 5, 11, 0, 63 };
        assertEquals(Pair.minMax(array), Pair.of(0, 77));
    }

    private class PairTestComparator<T> implements Comparator<T> {
        @Override
        public int compare(T o1, T o2) {
            return (int) o1 - (int) o2;
        }
    }

    @Test
    public void testMinMax2() {
        Integer[] array = new Integer[] { 77, 3, 5, 11, 0, 63 };

        assertEquals(Pair.minMax(array, new PairTestComparator<Integer>()), Pair.of(0, 77));
    }

    @Test
    public void testSwap() {
        assertEquals(Pair.swap(p3), Pair.of(43, 15));
    }

    @Test
    public void testToString() {
        assertEquals(p1.toString(), "(5,3)");
    }
}
