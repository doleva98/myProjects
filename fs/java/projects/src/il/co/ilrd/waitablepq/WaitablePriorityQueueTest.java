/* ofek */
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
                    System.out.println("adding" + "size is" + pqsem.size());
                }
            }
        };

        Runnable removerRunnable = new Runnable() {
            @Override
            public void run() {
                while (true) {
                    System.out.println("removing from top" + pqsem.dequeue() + " size " + pqsem.size());
                }
            }
        };
        Runnable dequeuerRunnable = new Runnable() {
            @Override
            public void run() {
                while (true) {
                    System.out.println("removing from top" + pqsem.dequeue() + " size " + pqsem.size());
                }
            }
        };

        final int SIZE = 40;
        Thread[] adders = new Thread[SIZE];
        Thread[] deququers = new Thread[SIZE];
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
            deququers[i] = new Thread(dequeuerRunnable);
            deququers[i].start();
        }

        for (int i = 0; i < SIZE; ++i) {
            try {
                adders[i].join();
                removers[i].join();
                deququers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
