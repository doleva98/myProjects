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
    public static int i;

    public static void main(String[] args) {
        Producer3 producer = new Producer3();
        Consumer3[] consumer = new Consumer3[SIZE];

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

            for (int OneProducerMultipleConsumers.i = 0; OneProducerMultipleConsumers.i < OneProducerMultipleConsumers.SIZE; ++OneProducerMultipleConsumers.i) {
                try {
                    OneProducerMultipleConsumers.sema.acquire();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            ++OneProducerMultipleConsumers.counter;
            synchronized (OneProducerMultipleConsumers.class) {

                OneProducerMultipleConsumers.class.notifyAll();
            }

        }
    }
}

class Consumer3 extends Thread {

    public void run() {
        while (true) {
            synchronized (OneProducerMultipleConsumers.class) {

                OneProducerMultipleConsumers.sema.release();

                try {
                    while
                    OneProducerMultipleConsumers.class.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                System.out.println(OneProducerMultipleConsumers.counter);
            }
        }
    }
}
