/*
 in dir: fs/java/projects/src/il/co/ilrd/linkedlist
 
 shiraz code review
  */
package il.co.ilrd.linkedlist;

public class SinglyLinkedList {

    private Snode head;

    public void pushFront(Object data) {
        head = new Snode(data, head);
    }

    public Object popFront() {
        if (isEmpty()) {
            return null;
        }
        Object data = head.data;
        head = head.next;
        return data;
    }

    public int getSize() {

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

    public GenericIter begin() {
        if (isEmpty()) {
            return null;
        }
        return new ListIterator(head);
    }

    public GenericIter find(Object data) {
        if (isEmpty()) {
            return null;
        }
        GenericIter iter = begin();
        GenericIter returnIter = begin();

        while (iter.hasNext() && !iter.next().equals(data)) {
            returnIter.next();
        }
        return returnIter;
    }

    private class ListIterator implements GenericIter {
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
        public Object next() {
            Object data = node.data;
            node = node.next;
            return data;
        }
    }

    private class Snode {
        private Snode next;
        private Object data;

        /* constructor method */
        private Snode(Object data, Snode next) {
            this.data = data;
            this.next = next;
        }
    }

}
