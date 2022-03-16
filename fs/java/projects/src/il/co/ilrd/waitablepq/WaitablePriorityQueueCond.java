/* ofek */
package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQueueCond<T> {
    private volatile Queue<T> queue;/* needs to be PriorityQueue */
    private final int CAPACITY;
    private final static int INITIALIZECAPACITY = 11;
    private AtomicInteger size = new AtomicInteger(0);
    private AtomicReference<Queue<T>> cache = new AtomicReference<>();
    private final Lock lock = new ReentrantLock();
    private final Condition notFull = lock.newCondition();
    private final Condition notEmpty = lock.newCondition();

    public WaitablePriorityQueueCond() {
        this(INITIALIZECAPACITY);
    }

    public WaitablePriorityQueueCond(int capacity) {
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        queue = new PriorityQueue<>(capacity);
        this.CAPACITY = capacity;
        cache.set(queue);
    }

    public WaitablePriorityQueueCond(int capacity, Comparator<? super T> comp) {
        Objects.requireNonNull(comp);
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        queue = new PriorityQueue<>(capacity, comp);
        this.CAPACITY = capacity;
        cache.set(queue);
    }

    public void enqueue(T data) {
        lock.lock();
        try {
            while (size.get() == CAPACITY) {
                try {
                    notFull.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            Queue<T> tempQueue = cache.get();
            tempQueue.add(data);
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
            size.incrementAndGet();
            notEmpty.signal();
        } finally {
            lock.unlock();
        }
    }

    public T dequeue() {
        T ret = null;
        lock.lock();
        try {
            while (isEmpty()) {
                try {
                    notEmpty.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            Queue<T> tempQueue = cache.get();
            ret = queue.poll();
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
            size.decrementAndGet();
            notFull.signal();
        } finally {
            lock.unlock();
        }
        return ret;
    }

    public boolean remove(T data) {
        boolean ret;
        lock.lock();
        try {
            while (isEmpty()) {
                try {
                    notEmpty.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            Queue<T> tempQueue = cache.get();
            ret = queue.remove(data);
            if (!cache.compareAndSet(queue, tempQueue)) {
                throw new CompareAndSetException("bad in compare and set");
            }
            size.decrementAndGet();
            notFull.signal();
        } finally {
            lock.unlock();
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
