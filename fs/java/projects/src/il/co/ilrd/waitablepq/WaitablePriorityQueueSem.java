package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQueueSem<T> {
    private Queue<T> queue;/* needs to be PriorityQueue */
    private Semaphore semaphoreFreeSize;
    private Semaphore semaphoreCurrSize = new Semaphore(0);
    private final static int INITIALIZECAPACITY = 11;
    private AtomicReference<Queue<T>> cache = new AtomicReference<>();
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
        lock.lock();
        try {
            Queue<T> tempQueue = cache.get();
            tempQueue.add(data);
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
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
            Queue<T> tempQueue = cache.get();
            ret = queue.poll();
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
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
            Queue<T> tempQueue = cache.get();
            ret = queue.remove(data);
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
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
            Queue<T> tempQueue = cache.get();
            sizeOfElements = queue.size();
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
        } finally {
            lock.unlock();
        }
        return sizeOfElements;
    }

    public boolean isEmpty() {
        boolean bool = false;
        lock.lock();
        try {
            Queue<T> tempQueue = cache.get();
            bool = queue.isEmpty();
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
        } finally {
            lock.unlock();
        }
        return bool;
    }
}