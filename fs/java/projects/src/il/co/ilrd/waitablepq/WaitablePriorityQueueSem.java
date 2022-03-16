package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQueueSem<T> {
    private volatile Queue<T> queue;/* needs to be PriorityQueue */
    private Semaphore semaphoreFreeSize;
    private Semaphore semaphoreCurrSize = new Semaphore(0);
    private final static int INITIALIZECAPACITY = 11;
    private final Lock lock = new ReentrantLock();

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
        lock.lock();
        try {
            queue.add(data);
            semaphoreCurrSize.release();
        } finally {
            lock.unlock();
        }
    }

    public T dequeue() {
        try {
            semaphoreCurrSize.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        T ret;
        lock.lock();
        try {
            ret = queue.poll();
            semaphoreFreeSize.release();
        } finally {
            lock.unlock();
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
        lock.lock();
        try {
            ret = queue.remove(data);
            semaphoreFreeSize.release();
        } finally {
            lock.unlock();
        }
        return ret;
    }

    public int size() {
        int sizeOfElements = 0;
        lock.lock();
        try {
            sizeOfElements = queue.size();
        } finally {
            lock.unlock();
        }
        return sizeOfElements;
    }

    public boolean isEmpty() {
        boolean bool = false;
        lock.lock();
        try {
            bool = queue.isEmpty();
        } finally {
            lock.unlock();
        }
        return bool;
    }
}