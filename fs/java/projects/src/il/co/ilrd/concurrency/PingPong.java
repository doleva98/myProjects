package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;

public class PingPong {
    public static Semaphore pingSema;
    public static Semaphore pongSema;

    public static void main(String[] args) {

        pingSema = new Semaphore(1);
        pongSema = new Semaphore(0);

        Producer producer = new Producer();
        Consumer consumer = new Consumer();

        producer.start();
        consumer.start();

        try {
            producer.join();
            consumer.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Producer extends Thread {
    public void run() {
        while (true) {
            try {
                PingPong.pingSema.acquire();
                System.out.println("Ping!");
                PingPong.pongSema.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }
}

class Consumer extends Thread {

    public void run() {
        while (true) {
            try {
                PingPong.pongSema.acquire();
                System.out.println("Pong!");
                PingPong.pingSema.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
