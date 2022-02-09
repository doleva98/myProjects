/*
 in dir: fs/java/projects/src/il/co/ilrd/linkedlist
 
  */

public class SinglyLinkedList {

    private Snode head;
    private ListIterator iter;

    private class ListIterator implements GenericIter {
        private Snode node;

        /* constructor method */
        private ListIterator() {
            this.node = null;
        }

        @Override
        public boolean hasNext() {
            return this.node.next != null;
        }

        @Override
        public void next() {
            this.node = this.node.next;
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
        this.head = null;
        this.iter = new ListIterator();
    }

    public void pushFront(Object data) {
        Snode node = new Snode(data, this.head);
        this.head = node;
    }

    public Object popFront() {
        Object data = this.head.data;
        this.head = this.head.next;
        return data;
    }

    public int getSize() {
        this.begin();
        int count = 1;
        if (this.isEmpty()) {
            return 0;
        }
        while (this.iter.hasNext()) {
            ++count;
            this.iter.next();
        }
        return count;
    }

    public boolean isEmpty() {
        return this.head == null;
    }

    public void begin() {
        this.iter.node = this.head;
    }

    public Object find(Object data) {
        this.begin();
        while (this.iter.hasNext()) {
            if (data.equals(this.iter.node.data)) {
                return this.iter.node.data;
            }
            iter.next();
        }
        return null;
    }

}
