/* ofek */
package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQueueCond<T> {
    private final Queue<T> queue;/* needs to be PriorityQueue */
    private final int CAPACITY;
    private final static int INITIALIZECAPACITY = 11;
    private final Lock lock = new ReentrantLock();
    private final Condition notFull = lock.newCondition();
    private final Condition notEmpty = lock.newCondition();

    public WaitablePriorityQueueCond() {
        this(INITIALIZECAPACITY, null);
    }

    public WaitablePriorityQueueCond(int capacity) {
        this(capacity, null);
    }

    public WaitablePriorityQueueCond(int capacity, Comparator<? super T> comp) {
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        queue = new PriorityQueue<>(capacity, comp);
        CAPACITY = capacity;
    }

    public void enqueue(T data) {
        lock.lock();
        try {
            while (size() == CAPACITY) {
                notFull.await();
            }
            queue.add(data);
            notEmpty.signal();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
    }

    public T dequeue() {
        T ret = null;
        lock.lock();
        try {
            while (isEmpty()) {
                notEmpty.await();
            }
            ret = queue.poll();
            notFull.signal();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
        return ret;
    }

    public boolean remove(T data) {
        boolean ret = false;
        lock.lock();
        try {
            ret = queue.remove(data);
            if (ret) {
                notFull.signal();
            }
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
