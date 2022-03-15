package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.locks.Condition;

public class WaitablePriorityQueueCond<T> {
    private volatile Queue<T> queue;/* needs to be PriorityQueue */
    private final int CAPACITY;
    private static int INITIALIZECAPACITY = 11;

    public WaitablePriorityQueueCond() {
        this(INITIALIZECAPACITY);
    }

    public WaitablePriorityQueueCond(int capacity) {
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        queue = new PriorityQueue<>(capacity);
        this.CAPACITY = capacity;
    }

    public WaitablePriorityQueueCond(int capacity, Comparator<? super T> comp) {
        Objects.requireNonNull(comp);
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        queue = new PriorityQueue<>(capacity, comp);
        this.CAPACITY = capacity;
    }

    public void enqueue(T data) {
        synchronized (this) {
            while (queue.size() == CAPACITY) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            queue.add(data);
            this.notifyAll();
        }
    }

    public T dequeue() {
        T ret = null;
        synchronized (this) {
            while (queue.size() == 0) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            ret = queue.poll();
            this.notifyAll();
        }
        return ret;
    }

    public boolean remove(T data) {
        boolean ret;
        synchronized (this) {
            while (queue.size() == 0) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            ret = queue.remove(data);
            this.notifyAll();
        }
        return ret;
    }

    public int size() {
        synchronized (this) {
            return queue.size();
        }
    }

    public boolean isEmpty() {
        synchronized (this) {
            return queue.isEmpty();
        }
    }
}
