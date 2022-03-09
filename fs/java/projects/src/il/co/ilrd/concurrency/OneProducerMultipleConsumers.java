package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class OneProducerMultipleConsumers {
    final static int SIZE = 5;
    private static final int SEMASIZE = 0;
    public static Semaphore sema = new Semaphore(SEMASIZE);
    public static int counter = 0;
    final static Lock lock = new ReentrantLock();
    static Condition wasProduced;

    public static void main(String[] args) {
        Producer3 producer = new Producer3();
        Consumer3[] consumer = new Consumer3[SIZE];
        wasProduced = lock.newCondition();
        producer.start();

        for (int i = 0; i < SIZE; ++i) {
            consumer[i] = new Consumer3();

            consumer[i].start();
        }
        try {
            producer.join();
        } catch (InterruptedException e1) {
            e1.printStackTrace();
        }

        for (int i = 0; i < SIZE; ++i) {

            try {
                consumer[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class Producer3 extends Thread {
    public void run() {
        while (true) {
            try {
                OneProducerMultipleConsumers.sema.acquire(OneProducerMultipleConsumers.SIZE);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            OneProducerMultipleConsumers.lock.lock();
            try {
                ++OneProducerMultipleConsumers.counter;

            } finally {
                OneProducerMultipleConsumers.lock.unlock();
            }
            OneProducerMultipleConsumers.wasProduced.signalAll();

        }
    }
}

class Consumer3 extends Thread {

    public void run() {
        while (true) {

            OneProducerMultipleConsumers.lock.lock();
            try {

                OneProducerMultipleConsumers.wasProduced.wait();

                OneProducerMultipleConsumers.sema.release();
                System.out.println(OneProducerMultipleConsumers.counter);
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                OneProducerMultipleConsumers.lock.unlock();
            }
        }
    }
}
