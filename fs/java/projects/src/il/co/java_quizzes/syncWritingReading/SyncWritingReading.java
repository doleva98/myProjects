package il.co.java_quizzes.syncWritingReading;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SyncWritingReading {
    private AtomicInteger cnt = new AtomicInteger();
    private final Lock lock = new ReentrantLock();

    public void startRead() {
        lock.lock();
        try {
            cnt.incrementAndGet();
        } finally {
            lock.unlock();
        }
    }

    public void endRead() {
        cnt.decrementAndGet();
    }

    // Implement this function
    public void startWrite() {
        lock.lock();
        while (cnt.get() != 0) {
        }
    }

    public void endWrite() {
        lock.unlock();
    }

}