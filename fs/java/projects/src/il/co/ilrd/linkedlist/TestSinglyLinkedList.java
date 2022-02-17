
package il.co.ilrd.linkedlist;

public class TestSinglyLinkedList {
    public static int getLineNumber() {
        return Thread.currentThread().getStackTrace()[2].getLineNumber();
    }

    public static void main(String[] args) {
        SinglyLinkedList slist = new SinglyLinkedList();

        if (slist.getSize() != 0) {
            System.out.println("fail in " + getLineNumber());
        }

        if (!slist.isEmpty()) {
            System.out.println("fail in " + getLineNumber());
        }

        slist.pushFront(4);

        if (slist.getSize() != 1) {
            System.out.println("fail in " + getLineNumber());
        }

        if (slist.isEmpty()) {
            System.out.println("fail in " + getLineNumber());
        }

        slist.pushFront("hello world");

        if (slist.getSize() != 2) {
            System.out.println("fail in " + getLineNumber());
        }

        for (int i = 0; i < 50; ++i) {
            slist.pushFront(i);
        }

        if (slist.getSize() != 52) {
            System.out.println("fail in " + getLineNumber());
        }

        if (slist.find("hello world") == null) {
            System.out.println("fail in " + getLineNumber());
        }

        if (slist.find(30) == null) {
            System.out.println("fail in " + getLineNumber());
        }

        if (slist.find(4) == null) {
            System.out.println("fail in " + getLineNumber());
        }

        GenericIter iter = slist.begin();

        for (int i = 0; i < 50; ++i) {
            if ((int) iter.next() != 49 - i) {
                System.out.println("fail in " + getLineNumber());
            }
            if (!iter.hasNext()) {
                System.out.println("fail in " + getLineNumber());
            }
        }

        if (iter.next().equals(4)) {
            System.out.println("fail in " + getLineNumber());

        }

        for (int i = 0; i < 50; ++i) {
            if ((int) slist.popFront() != 49 - i) {
                System.out.println("fail in " + getLineNumber());
            }
        }

        if (slist.getSize() != 2) {
            System.out.println("fail in " + getLineNumber());
        }

    }

}
