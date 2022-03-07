package il.co.ilrd.concurrency;

import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.locks.ReentrantLock;

public class CostOfLocking extends Thread {
    private static volatile long globalCounter = 0;
    private static AtomicLong al;
    private static Counter counter;
    private static ReentrantLock re;

    public static void main(String[] args) {
        CostOfLocking t1 = new CostOfLocking();
        CostOfLocking t2 = new CostOfLocking();
        al = new AtomicLong(0);
        counter = new Counter();
        re = new ReentrantLock();

        long startTime = System.nanoTime();

        t1.start();
        t2.start();
        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        long endTime = System.nanoTime();

        System.out.println(globalCounter);
        /* System.out.println(Counter.globalCounter); */
        System.out.println("nano time is " + (endTime - startTime));
    }

    public void run() {
        syncBlockIncrement();
        /*atomicIncrement(); 
        syncMethodIncrement();*/
        /* reentrentLockIncrement(); */
    }

    private void syncBlockIncrement() {
        for (int i = 0; i < 10000000; ++i) {
            synchronized (CostOfLocking.class) {
                ++globalCounter;
            }
        }

    }

    private void atomicIncrement() {
        for (int i = 0; i < 10000000; ++i) {
            al.incrementAndGet();

        }
    }

    private void syncMethodIncrement() {
        for (int i = 0; i < 10000000; ++i) {
            counter.increment();

        }
    }

    private void reentrentLockIncrement() {
        for (int i = 0; i < 10000000; ++i) {

            try {
                re.lock();

                ++globalCounter;
            } finally {
                re.unlock();
            }

        }

    }
}

class Counter {
    public static volatile long globalCounter = 0;

    public synchronized void increment() {
        ++globalCounter;
    }
}