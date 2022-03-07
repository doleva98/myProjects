package il.co.ilrd.concurrency;

public class LinkedListSynchronized {

    public static void main(String[] args) {
        Producer producer = new Producer();
        Consumer consumer = new Consumer();

        producer.start();
        consumer.start();

        try {
            producer.join();
            consumer.join();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

}

class Producer extends Thread {
    public void run() {

    }
}

class Consumer extends Thread {

    public void run() {

    }
}
