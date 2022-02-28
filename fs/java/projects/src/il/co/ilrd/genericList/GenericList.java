package il.co.ilrd.genericList;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class GenericList<T> implements Iterable<T> {
    private Snode head;

    public void pushFront(T data) {
        head = new Snode(data, head);
    }

    public T popFront() {
        if (isEmpty()) {
            return null;
        }
        T data = head.data;
        head = head.next;
        return data;
    }

    public int size() {

        if (isEmpty()) {
            return 0;
        }

        GenericIter iter = begin();
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

    public GenericList<T> newReverse() {

    }

    public static <T> GenericList<T> merge(GenericList<T> l1, GenericList<T> l2) {

    }

    @Override
    public Iterator<T> iterator() {
        if (isEmpty()) {
            return null;
        }
        return new ListIterator(head);
    }

    private class ListIterator implements Iterator<T> {
        private Snode node;

        /* constructor method */
        private ListIterator(Snode node) {
            this.node = node;
        }

        @Override
        public boolean hasNext() {
            return node != null;
        }

        @Override
        public T next() throws ConcurrentModificationException{
            T data = node.data;
            node = node.next;
            return data;
        }

    }

    private class Snode {
        private Snode next;
        private T data;

        /* constructor method */
        private Snode(T data, Snode next) {
            this.data = data;
            this.next = next;
        }
    }

}
