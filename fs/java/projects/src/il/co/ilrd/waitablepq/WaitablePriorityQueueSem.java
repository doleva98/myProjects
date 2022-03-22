package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQueueSem<T> {
    private final Queue<T> queue;
    private final Semaphore semaphoreFreeSize;
    private final Semaphore semaphoreCurrSize = new Semaphore(0);
    private final static int INITIALIZECAPACITY = 11;
    private final Lock lock = new ReentrantLock();

    public WaitablePriorityQueueSem() {
        this(INITIALIZECAPACITY, null);
    }

    public WaitablePriorityQueueSem(int capacity) {
        this(capacity, null);

    }

    public WaitablePriorityQueueSem(int capacity, Comparator<? super T> comp) {
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
        } finally {
            lock.unlock();
        }
        semaphoreCurrSize.release();
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
        } finally {
            lock.unlock();
        }
        semaphoreFreeSize.release();
        return ret;
    }

    public boolean remove(T data) {
        boolean ret = false;
        if (semaphoreCurrSize.tryAcquire()) {
            lock.lock();
            ret = queue.remove(data);
            lock.unlock();
            if (ret) {
                semaphoreFreeSize.release();
            } else {
                semaphoreCurrSize.release();
            }
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