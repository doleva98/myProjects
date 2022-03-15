package il.co.java_quizzes.threadsafeFSQ;

import java.util.LinkedList;
import java.util.List;

class ThreadSafeFSQ<T> {
    private List<T> list;
    private int capacity;
    private int size;

    public ThreadSafeFSQ(int capacity) {
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        list = new LinkedList<>();
        this.capacity = capacity;
        size = 0;
    }

    synchronized public T poll() {
        --size;
        while (size <= 0) {
            try {
                this.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        if (size < capacity) {
            this.notifyAll();
        }
        return list.remove(0);
    }

    public T peek() {
        return list.get(0);
    }

    synchronized public boolean offer(T element) {
        while (size >= capacity && size <= 0) {
            try {
                this.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        if (size < capacity) {
            this.notifyAll();
        }
        list.add(size, element);
        ++size;
        return true;
    }

    public static void main(String[] args) {
        ThreadSafeFSQ<Integer> q = new ThreadSafeFSQ<>(5);
        Thread t1 = new Thread(new Runnable() {

            @Override
            public void run() {
                int i = 0;
                while (true) {
                    System.out.println("adding" + i++);
                    q.offer(5);
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }

        });
        Thread t2 = new Thread(new Runnable() {

            @Override
            public void run() {
                while (true) {
                    System.out.println("polling");
                    q.poll();
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }

        });

        t1.start();
        t2.start();
    }
}
