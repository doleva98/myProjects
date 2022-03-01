package il.co.ilrd.genericList;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class GenericList<E> implements Iterable<E> {
    private Snode<E> head;
    private int versionNum; /* long */

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

        while (iter.hasNext()) {
            ret_list.pushFront(iter.next());
        }
        return ret_list;
    }

    public static <E> GenericList<E> merge(GenericList<E> l1, GenericList<E> l2) {

        /* Iterator<E> iter = l1.iterator();
        while (iter.hasNext()) {
            ret_list.pushFront(iter.next());
        }
        iter = l2.iterator();
        while (iter.hasNext()) {
            ret_list.pushFront(iter.next());
        }
        return newReverse(ret_list); */
        GenericList<E> ret_list = new GenericList<>();
        Iterator<E> iter;
        Snode<E> ret_list_node = ret_list.head;

        if (!l1.isEmpty()) {
            ret_list.pushFront(l1.head.data);
            iter = l1.iterator();
            iter.next();
            while (iter.hasNext()) {
                ret_list.pushBack(iter.next(), ret_list_node);
                ret_list_node = ret_list_node.next;
            }
        } else if (!l2.isEmpty()) {
            ret_list.pushFront(l2.head.data);
            iter = l2.iterator();
            while (iter.hasNext()) {
                ret_list.pushBack(iter.next(), ret_list_node);
                ret_list_node = ret_list_node.next;
            }
        }

        return ret_list;
    }

    @Override
    public Iterator<E> iterator() {
        return new ListIterator(head, versionNum);
    }

    private Snode<E> pushBack(E data, Snode<E> node) {
        ++versionNum;
        return node.next = new Snode<>(data, null);
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
