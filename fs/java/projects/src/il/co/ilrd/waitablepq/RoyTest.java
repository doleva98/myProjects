package il.co.ilrd.waitablepq;

class RoyTest {
    public static void main(String[] args) {
        final int NUM_OF_PRODUCERS = 10;
        final int NUM_OF_CONSUMERS = 10;
        WaitablePriorityQueueCond<Integer> wpqCond = new WaitablePriorityQueueCond<>(5);
        WaitablePriorityQueueSem<Integer> wpqSem = new WaitablePriorityQueueSem<>(5);
        Runnable producerRunnableCond = new Runnable() {
            @Override
            public void run() {
                System.out.println("cond producer thread: " + Thread.currentThread().getName());
                for (int i = 0; i < 5; ++i) {
                    wpqCond.enqueue(i);
                    System.out.println("adding");
                    System.out.println("size is " + wpqCond.size());
                }
            }
        };
        Runnable consumerRunnableCond = new Runnable() {
            @Override
            public void run() {
                System.out.println("cond consumer thread: " + Thread.currentThread().getName());
                for (int i = 0; i < 5; ++i) {
                    System.out.println("removing " + wpqCond.dequeue());
                    System.out.println("size is " + wpqCond.size());
                }
                System.out.println("removing 1: " + wpqCond.remove(1));
            }
        };
        Runnable producerRunnableSem = new Runnable() {
            @Override
            public void run() {
                System.out.println("sem producer thread: " + Thread.currentThread().getName());
                for (int i = 0; i < 5; ++i) {
                    wpqSem.enqueue(i);
                    System.out.println("adding");
                    System.out.println("size is " + wpqSem.size());
                }
            }
        };
        Runnable consumerRunnableSem = new Runnable() {
            @Override
            public void run() {
                System.out.println("sem consumer thread: " + Thread.currentThread().getName());
                for (int i = 0; i < 5; ++i) {
                    System.out.println("dequeueing " + wpqSem.dequeue());
                    System.out.println("size is " + wpqSem.size());
                }
                System.out.println("removing 1: " + wpqSem.remove(1));
            }
        };
        Thread[] producers = new Thread[NUM_OF_PRODUCERS];
        Thread[] consumers = new Thread[NUM_OF_CONSUMERS];

        for (int i = 0; i < NUM_OF_PRODUCERS; ++i) {
            producers[i] = new Thread(producerRunnableCond);
            producers[i].start();
        }
        for (int i = 0; i < NUM_OF_CONSUMERS; ++i) {
            consumers[i] = new Thread(consumerRunnableCond);
            consumers[i].start();
        }
        for (int i = 0; i < NUM_OF_PRODUCERS; ++i) {
            try {
                producers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        for (int i = 0; i < NUM_OF_CONSUMERS; ++i) {

            try {
                consumers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        for (int i = 0; i < NUM_OF_PRODUCERS; ++i) {

            producers[i] = new Thread(producerRunnableSem);
            producers[i].start();
        }
        for (int i = 0; i < NUM_OF_CONSUMERS; ++i) {

            consumers[i] = new Thread(consumerRunnableSem);
            consumers[i].start();
        }
        for (int i = 0; i < NUM_OF_PRODUCERS; ++i) {

            try {
                producers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        for (int i = 0; i < NUM_OF_CONSUMERS; ++i) {

            try {
                consumers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("fdsfdf");
    }
}
