package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicReference;

public class WaitablePriorityQueueSem<T> {
    private Queue<T> queue;/* needs to be PriorityQueue */
    private Semaphore semaphoreFreeSize;
    private Semaphore semaphoreCurrSize = new Semaphore(0);
    private final static int INITIALIZECAPACITY = 11;
    private AtomicReference<Queue<T>> cache = new AtomicReference<>();

    public WaitablePriorityQueueSem() {
        this(INITIALIZECAPACITY);
    }

    public WaitablePriorityQueueSem(int capacity) {
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        queue = new PriorityQueue<>(capacity);
        semaphoreFreeSize = new Semaphore(capacity);
        cache.set(queue);
    }

    public WaitablePriorityQueueSem(int capacity, Comparator<? super T> comp) {
        Objects.requireNonNull(comp);
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        queue = new PriorityQueue<>(capacity, comp);
        semaphoreFreeSize = new Semaphore(capacity);
        cache.set(queue);
    }

    public void enqueue(T data) {
        try {
            semaphoreFreeSize.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        synchronized (this) {
            Queue<T> tempQueue = cache.get();
            tempQueue.add(data);
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
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
            Queue<T> tempQueue = cache.get();
            ret = queue.poll();
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
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
        boolean ret;
        synchronized (this) {
            Queue<T> tempQueue = cache.get();
            ret = queue.remove(data);
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
            semaphoreFreeSize.release();
        }
        return ret;
    }

    public int size() {
        int sizeOfElements = 0;
        synchronized (this) {
            Queue<T> tempQueue = cache.get();
            sizeOfElements = queue.size();
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
        }
        return sizeOfElements;
    }

    public boolean isEmpty() {
        boolean bool = false;
        synchronized (this) {
            Queue<T> tempQueue = cache.get();
            bool = queue.isEmpty();
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
        }
        return bool;
    }
}