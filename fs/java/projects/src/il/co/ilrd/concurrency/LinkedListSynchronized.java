package il.co.ilrd.concurrency;

import java.util.ArrayList;
import java.util.List;

public class LinkedListSynchronized {
    public static final Object o = new Object();
    public static List<Integer> list = new ArrayList<>();

    public static void main(String[] args) {
        final int SIZE = 50;
        Producer1[] producer = new Producer1[SIZE];
        Consumer1[] consumer = new Consumer1[SIZE];
        for (int i = 0; i < SIZE; ++i) {
            producer[i] = new Producer1();
            consumer[i] = new Consumer1();

            producer[i].start();
            consumer[i].start();
        }
        for (int i = 0; i < SIZE; ++i) {

            try {
                producer[i].join();
                consumer[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}

class Producer1 extends Thread {
    public void run() {
        while (true) {
            synchronized (LinkedListSynchronized.o) {
                System.out.println("adding 1 to list");
                LinkedListSynchronized.list.add(1);
            }
        }
    }
}

class Consumer1 extends Thread {

    public void run() {
        while (true) {
            synchronized (LinkedListSynchronized.o) {
                System.out.println("removing 1 to list");
                if(!LinkedListSynchronized.list.isEmpty())
                {
                    LinkedListSynchronized.list.remove(0);
                }
            }
        }
    }
}
