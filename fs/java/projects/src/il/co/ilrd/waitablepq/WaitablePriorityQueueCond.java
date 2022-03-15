package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

public class WaitablePriorityQueueCond<T> {
    private AtomicReference
    private volatile Queue<T> queue;/* needs to be PriorityQueue */
    private final int CAPACITY;
    private final static int INITIALIZECAPACITY = 11;
    private AtomicInteger size = new AtomicInteger(0);

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
            while (size.get() == CAPACITY) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            queue.add(data);
            size.incrementAndGet();
            this.notifyAll();
        }
    }

    public T dequeue() {
        T ret = null;
        synchronized (this) {
            while (isEmpty()) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            ret = queue.poll();
            size.decrementAndGet();
            this.notifyAll();
        }
        return ret;
    }

    public boolean remove(T data) {
        boolean ret;
        synchronized (this) {
            while (isEmpty()) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            ret = queue.remove(data);
            size.decrementAndGet();
            this.notifyAll();
        }
        return ret;
    }

    public int size() {
        return size.get();
    }

    public boolean isEmpty() {
        return size.get() == 0;
    }
}
