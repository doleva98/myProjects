package il.co.ilrd.concurrency;

import java.util.concurrent.atomic.AtomicBoolean;

public class PingPongAtomic {
    public static AtomicBoolean isConsumer = new AtomicBoolean();

    public static void main(String[] args) {

        ProducerAtomic producer = new ProducerAtomic();
        ConsumerAtomic consumer = new ConsumerAtomic();

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

class ProducerAtomic extends Thread {
    public void run() {
        while (true) {
            if (!PingPongAtomic.isConsumer.get()) {
                System.out.println("Ping!");
                PingPongAtomic.isConsumer.set(true);
            }
        }
    }
}

class ConsumerAtomic extends Thread {

    public void run() {
        while (true) {
            if (PingPongAtomic.isConsumer.get()) {
                System.out.println("Pong!");
                PingPongAtomic.isConsumer.set(false);
            }
        }
    }
}
