package il.co.ilrd.concurrency;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;

public class LinkedListSynchronizedSema {
    public static final Object o = new Object();
    public static List<Integer> list = new ArrayList<>();
    private static final int SEMASIZE = 0;
    public static Semaphore sema = new Semaphore(SEMASIZE);

    public static void main(String[] args) {
        final int SIZE = 50;
        Producer2[] producer = new Producer2[SIZE];
        Consumer2[] consumer = new Consumer2[SIZE];
        for (int i = 0; i < SIZE; ++i) {
            producer[i] = new Producer2();
            consumer[i] = new Consumer2();

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

class Producer2 extends Thread {
    public void run() {
        while (true) {
            synchronized (LinkedListSynchronizedSema.o) {
                System.out.println("adding 1 to list");
                LinkedListSynchronizedSema.list.add(1);
            }
            LinkedListSynchronizedSema.sema.release();
        }
    }
}

class Consumer2 extends Thread {

    public void run() {
        while (true) {
            try {
                LinkedListSynchronizedSema.sema.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            synchronized (LinkedListSynchronizedSema.o) {
                System.out.println("removing 1 to list");
                LinkedListSynchronizedSema.list.remove(0);
            }
        }
    }
}
