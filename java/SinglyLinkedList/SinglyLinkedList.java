class SinglinkedList {

    private Snode head;

    public SinglinkedList() {

    }

    public void pushFront(Object data) {
    }

    public void popFront() {
    }

    public int getSize() {
    }

    public boolean isEmpty()
    {}

    public Object find(Object data) {
        return data;
    }

    public void begin(Iterator iter){}
    

    private class Snode {
        private Object data;
        private Snode next;

        Snode(Object data) {
            this.data = data;
        }

        Snode() {
        }

        public Object getData() {
            return this.data;
        }

        public void setData(Object data) {
            this.data = data;
        }

        public Snode getNext() {
            return this.next;
        }

        public void setNode(Snode next) {
            this.next = next;
        }

    }
}

interface GenericIterator {
    public boolean hasNext();

    public Object next();
}
