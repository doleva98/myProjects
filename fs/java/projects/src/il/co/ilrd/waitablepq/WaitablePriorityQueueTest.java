package il.co.ilrd.waitablepq;

public class WaitablePriorityQueueTest {
    public static void main(String[] args) {
        WaitablePriorityQueueSem<Integer> pqsem = new WaitablePriorityQueueSem<>();
        pqsem.enqueue(1);
        pqsem.dequeue();
        pqsem.enqueue(1);
        pqsem.remove(1);
        Runnable adderRunnable = new Runnable() {
            @Override
            public void run() {
                while (true) {
                    pqsem.enqueue(5);
                    System.out.println("adding");
                }
            }
        };

        Runnable removerRunnable = new Runnable() {
            @Override
            public void run() {
                while (true) {
                    System.out.println("removing from top" + pqsem.dequeue());
                    /* change to remove if wanna check this */
                }
            }
        };
        final int SIZE = 40;
        Thread[] adders = new Thread[40];
        Thread[] removers = new Thread[40];

        for (Thread adder : adders) {
            adder = new Thread(adderRunnable);
            adder.start();
        }

        for (Thread remover : removers) {
            remover = new Thread(removerRunnable);
            remover.start();
        }

        for (int i = 0; i < SIZE; ++i) {
            try {
                adders[i].join();
                removers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
