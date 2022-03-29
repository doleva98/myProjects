package il.co.java_quizzes.genericLinkedListQuiz;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class GenericLinkedListQuiz<T> implements Iterable<T> {

    private Node<T> head = null;
    private static int versionNumStartNumber = Integer.MIN_VALUE;
    private int versionNum = versionNumStartNumber;

    @Override
    public Iterator<T> iterator() {
        return new LinkedListIterator(head, versionNum);
    }

    public void pushFront(T val) {
        updateVersion();
        head = new Node<>(val, head);
    }

    public T popFront(T val) {
        if (isEmpty()) {
            return null;
        }
        updateVersion();
        T ret = head.val;
        head = head.next;
        return ret;
    }

    public boolean isEmpty() {
        return head == null;
    }

    public int size() {
        int count = 0;
        for (T t : this) {
            ++count;
            t.toString();
        }
        return count;
    }

    public T find(T val) {
        if (isEmpty()) {
            return null;
        }
        Iterator<T> iter1 = iterator();
        Iterator<T> iter2 = iterator();
        T ret = null;
        while (iter1.hasNext() && !iter1.next().equals(val)) {
            ret = iter2.next();
        }
        return ret;
    }

    private class LinkedListIterator implements Iterator<T> {
        private Node<T> node = null;
        private int currVersionNum;

        LinkedListIterator(Node<T> node, int currVersionNum) {
            this.node = node;
            this.currVersionNum = currVersionNum;
        }

        @Override
        public boolean hasNext() {
            return node != null;
        }

        @Override
        public T next() {
            if (currVersionNum != versionNum) {
                throw new ConcurrentModificationException();
            }
            T ret = node.val;
            node = node.next;
            return ret;
        }

    }

    private static class Node<T> {
        T val = null;
        Node<T> next = null;

        private Node(T val, Node<T> next) {
            this.val = val;
            this.next = next;
        }
    }

    private void updateVersion() {
        if (versionNumStartNumber == Integer.MAX_VALUE) {
            versionNum = versionNumStartNumber;
        } else {
            ++versionNum;
        }
    }
}
