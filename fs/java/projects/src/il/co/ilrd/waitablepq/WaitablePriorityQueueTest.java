/* ofek */
package il.co.ilrd.waitablepq;

public class WaitablePriorityQueueTest {
    public static void main(String[] args) {
        WaitablePriorityQueueCond<Integer> pqsem = new WaitablePriorityQueueCond<>();
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
                    System.out.println("size is" + pqsem.size());
                }
            }
        };

        Runnable removerRunnable = new Runnable() {
            @Override
            public void run() {
                while (true) {
                    System.out.println("removing from top" + pqsem.dequeue() + " size " + pqsem.size());
                    /* change to remove if wanna check this */
                }
            }
        };
        final int SIZE = 40;
        Thread[] adders = new Thread[SIZE];
        Thread[] removers = new Thread[SIZE];

        for (int i = 0; i < SIZE; ++i) {
            adders[i] = new Thread(adderRunnable);
            adders[i].start();
        }

        for (int i = 0; i < SIZE; ++i) {
            removers[i] = new Thread(removerRunnable);
            removers[i].start();
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
