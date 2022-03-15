package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.Semaphore;

public class WaitablePriorityQueueSem<T> {
    private Queue<T> queue;/* needs to be PriorityQueue */
    private Semaphore semaphoreFreeSize;
    private Semaphore semaphoreCurrSize = new Semaphore(0);
    private final static int INITIALIZECAPACITY = 11;

    public WaitablePriorityQueueSem() {
        this(INITIALIZECAPACITY);
    }

    public WaitablePriorityQueueSem(int capacity) {
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        queue = new PriorityQueue<>(capacity);
        semaphoreFreeSize = new Semaphore(capacity);
    }

    public WaitablePriorityQueueSem(int capacity, Comparator<? super T> comp) {
        Objects.requireNonNull(comp);
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        queue = new PriorityQueue<>(capacity, comp);
        semaphoreFreeSize = new Semaphore(capacity);
    }

    public void enqueue(T data) {
        try {
            semaphoreFreeSize.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        synchronized (this) {
            queue.add(data);
            semaphoreCurrSize.release();
        }
    }

    public T dequeue() {
        try {
            semaphoreCurrSize.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        T ret;
        synchronized (this) {
            ret = queue.poll();
            semaphoreFreeSize.release();
        }
        return ret;
    }

    public boolean remove(T data) {
        try {
            semaphoreCurrSize.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        T ret;
        synchronized (this) {
            ret = queue.poll();
            semaphoreFreeSize.release();
        }
        return ret != null;
    }

    public int size() {
        int sizeOfElements = 0;
        synchronized (this) {
            sizeOfElements = queue.size();
        }
        return sizeOfElements;
    }

    public boolean isEmpty() {
        boolean bool = false;
        synchronized (this) {
            bool = queue.isEmpty();
        }
        return bool;
    }
}
