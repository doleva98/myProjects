package il.co.java_quizzes.syncProblem2;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SyncWritingReading {
    private final Semaphore sema;
    private final int maxReaders;
    private final Lock lock = new ReentrantLock();

    public SyncWritingReading(int maxReaders) {
        sema = new Semaphore(maxReaders);
        this.maxReaders = maxReaders;
    }

    public void startRead() {
        lock.lock();
        try {
            sema.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
    }

    public void endRead() {
        sema.release();
    }

    // Implement this function
    public void startWrite() {
        lock.lock();

        try {
            sema.acquire(maxReaders);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void endWrite() {
        sema.release(maxReaders);
        lock.unlock();
    }
}
