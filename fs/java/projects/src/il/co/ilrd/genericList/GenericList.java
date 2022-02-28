package il.co.ilrd.genericList;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class GenericList<E> implements Iterable<E> {
    private Snode<E> head;
    private int versionNum;

    public void pushFront(E data) {
        ++versionNum;
        head = new Snode<>(data, head);
    }

    public E popFront() {
        if (isEmpty()) {
            return null;
        }
        ++versionNum;
        E data = head.data;
        head = head.next;
        return data;
    }

    public int size() {

        if (isEmpty()) {
            return 0;
        }

        Iterator<E> iter = iterator();
        int count = 0;

        while (iter.hasNext()) {
            ++count;
            iter.next();
        }
        return count;
    }

    public boolean isEmpty() {
        return head == null;
    }

    public Iterator<E> find(E data) {
        if (isEmpty()) {
            return null;
        }
        Iterator<E> iter = iterator();
        Iterator<E> returnIter = iterator();

        while (iter.hasNext() && !iter.next().equals(data)) {
            returnIter.next();
        }
        return returnIter;
    }

    public static <E> GenericList<E> newReverse(GenericList<E> list) {
        GenericList<E> ret_list = new GenericList<>();
        Iterator<E> iter = list.iterator();
        E data_to_push = null;

        for (int i = 0; i < list.size(); ++i) {
            for (int j = 0; j < list.size() - i; ++j) {
                data_to_push = iter.next();
            }
            ret_list.pushFront(data_to_push);
            iter = list.iterator();
        }
        return ret_list;
    }

    public static <E> GenericList<E> merge(GenericList<E> l1, GenericList<E> l2) {
        GenericList<E> ret_list = new GenericList<>();
        Iterator<E> iter = l1.iterator();
        while (iter.hasNext()) {
            ret_list.pushFront(iter.next());
        }
        iter = l2.iterator();
        while (iter.hasNext()) {
            ret_list.pushFront(iter.next());
        }
        return ret_list;
    }

    @Override
    public Iterator<E> iterator() {
        if (isEmpty()) {
            return null;
        }
        return new ListIterator(head, versionNum);
    }

    private class ListIterator implements Iterator<E> {
        private Snode<E> node;
        private int iterVersionNum;

        /* constructor method */
        private ListIterator(Snode<E> node, int iterVersionNum) {
            this.node = node;
            this.iterVersionNum = iterVersionNum;
        }

        @Override
        public boolean hasNext() {
            return node != null;
        }

        @Override
        public E next() {
            if (iterVersionNum != versionNum) {
                throw new ConcurrentModificationException();
            }
            E data = node.data;
            node = node.next;
            return data;
        }

    }

    private static class Snode<T> {
        private T data;
        private Snode<T> next;

        /* constructor method */
        private Snode(T data, Snode<T> next) {
            this.data = data;
            this.next = next;
        }
    }

}
