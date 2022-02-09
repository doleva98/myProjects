/*
 in dir: fs/java/projects/src/il/co/ilrd/linkedlist
 
  */

public class SinglyLinkedList {

    private Snode head;

    private class ListIterator implements GenericIter {
        private Snode node;

        /* constructor method */
        private ListIterator(Snode node) {
            this.node = node;
        }

        @Override
        public boolean hasNext() {
            return this.node.next != null;
        }

        @Override
        public Object next() {
            Object data = this.node.data;
            this.node = this.node.next;
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

    /* constructor method */
    public SinglyLinkedList() {
    }

    public void pushFront(Object data) {
        Snode node = new Snode(data, this.head);
        this.head = node;
    }

    public Object popFront() {
        if (this.isEmpty()) {
            return null;
        }
        Object data = this.head.data;
        this.head = this.head.next;
        return data;
    }

    public int getSize() {
        if (this.isEmpty()) {
            return 0;
        }

        ListIterator iter = new ListIterator(this.head);
        int count = 1;

        while (iter.hasNext()) {
            ++count;
            iter.next();
        }
        return count;
    }

    public boolean isEmpty() {
        return this.head == null;
    }

    public GenericIter begin() {
        if (this.head == null) {
            return null;
        }
        return new ListIterator(this.head);
    }

    public GenericIter find(Object data) {
        ListIterator iter = new ListIterator(this.head);
        while (iter.hasNext()) {
            if (data.equals(iter.node.data)) {
                return iter;
            }
            iter.next();
        }
        return null;
    }

}
