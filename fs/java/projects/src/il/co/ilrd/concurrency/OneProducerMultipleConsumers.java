package il.co.ilrd.concurrency;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class OneProducerMultipleConsumers {
    public static final Object o = new Object();
    public static List<Integer> list = new ArrayList<>();
    private static final int SEMASIZE = 0;
    public static Semaphore sema = new Semaphore(SEMASIZE);
    public static String buffer;
    final static Lock lock = new ReentrantLock();
    final static Condition notFull = lock.newCondition();
    final static Condition notEmpty = lock.newCondition();
    final static int SIZE = 50;

    public static void main(String[] args) {
        Producer3 producer = new Producer3();
        Consumer2[] consumer = new Consumer2[SIZE];

        producer.start();

        for (int i = 0; i < SIZE; ++i) {
            consumer[i] = new Consumer2();

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
        OneProducerMultipleConsumers.lock.lock();

        OneProducerMultipleConsumers.buffer = "hello world";
        OneProducerMultipleConsumers.sema.release(OneProducerMultipleConsumers.SIZE);
        OneProducerMultipleConsumers.lock.unlock();
    }
}

class Consumer3 extends Thread {

    public void run() {
        OneProducerMultipleConsumers.lock.lock();
        System.out.println(OneProducerMultipleConsumers.buffer);
        try {
            OneProducerMultipleConsumers.sema.acquire();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        OneProducerMultipleConsumers.lock.unlock();
    }
}
