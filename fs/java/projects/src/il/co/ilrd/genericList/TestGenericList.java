package il.co.ilrd.genericList;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Iterator;

import org.junit.Before;
import org.junit.Test;

public class TestGenericList {
    GenericList<Integer> list;

    @Before
    public void before() {
        list = new GenericList<>();

    }

    @Test
    public void testFind() {
        list.pushFront(54);
        Iterator<Integer> iter = list.find(54);
        assertEquals(iter.next(), 54);

        list.popFront();
        int num_test = 80;

        for (int i = 0; i < num_test; ++i) {
            list.pushFront(i);
        }

        iter = list.find(54);
        assertEquals(iter.next(), 54);
    }

    @Test
    public void testIsEmpty() {
        assertTrue(list.isEmpty());
        list.pushFront(3);
        assertFalse(list.isEmpty());

    }

    @Test
    public void testIterator() {
        int num_test = 80;

        for (int i = 0; i < num_test; ++i) {
            list.pushFront(i);
        }

        Iterator<Integer> iter = list.iterator();

        while (iter.hasNext()) {
            assertEquals(iter.next(), --num_test);
        }
    }

    @Test
    public void testMerge() {
        GenericList<Integer> list2 = new GenericList<>();
        int num_test = 80;

        for (int i = 0; i < num_test; ++i) {
            list.pushFront(i);
            list2.pushFront(i);
        }
        GenericList<Integer> list3 = GenericList.merge(list, list2);

        int counter = num_test;
        for (int i : list3) {
            if (counter == 0) {
                counter = num_test;
            }
            assertEquals(i, --counter);
        }
    }

    @Test
    public void testNewReverse() {
        int num_test = 80;
        GenericList<Integer> list2 = GenericList.<Integer>newReverse(list);
        assertEquals(list2.size(), 0);
        assertTrue(list2.isEmpty());

        list.pushFront(1);
        list.pushFront(5);

        list2 = GenericList.<Integer>newReverse(list);
        assertEquals(list2.size(), 2);
        assertTrue(!list2.isEmpty());
        list.popFront();
        list.popFront();
        assertTrue(list.isEmpty());

        for (int i = 0; i < num_test; ++i) {
            list.pushFront(i);
        }

        list2 = GenericList.<Integer>newReverse(list);
        int counter = 0;
        for (int i : list2) {
            assertEquals(i, counter);
            ++counter;
        }
    }

    @Test
    public void testForEach() {
        int num_test = 80;

        for (int i = 0; i < num_test; ++i) {
            list.pushFront(i);
        }
        int counter = num_test;

        for (int i : list) {
            assertEquals(i, --counter);
        }
    }

    @Test
    public void testSize() {
        assertEquals(list.size(), 0);

        int num_test = 80;

        for (int i = 0; i < num_test; ++i) {
            list.pushFront(i);
            assertEquals(list.size(), i + 1);
        }
        for (int i = 0; i < num_test; ++i) {
            list.popFront();
            assertEquals(list.size(), num_test - 1 - i);
        }
    }
}
