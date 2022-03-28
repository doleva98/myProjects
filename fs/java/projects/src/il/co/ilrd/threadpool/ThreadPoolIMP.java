package il.co.ilrd.threadpool;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.Callable;
import java.util.concurrent.CancellationException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Future;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

import il.co.ilrd.waitablepq.WaitablePriorityQueueCond;

public class ThreadPoolIMP implements Executor {
    public enum Priority {
        LOW,
        MEDIUM,
        HIGH;
    }

    private final WaitablePriorityQueueCond<Task<?>> tasks;
    private final List<ThreadImp> threads;
    private final ReentrantLock threadPoolLock = new ReentrantLock();
    private final Condition threadPoolCond = threadPoolLock.newCondition();
    private final Semaphore sema = new Semaphore(0);
    private boolean isShutdown = false;
    private boolean isPaused = false;
    private int sizeBeforeShutdown = 0;/* for the semaphore , size of threads*/
    private final static int DEFAULTPRIORITY = Priority.MEDIUM.ordinal();
    private final static int SYSTEMPRIORITY = Priority.values().length;
    private final static int LOWESTPRIORITY = -1;

    public ThreadPoolIMP(int numOfThreads) {
        if (numOfThreads < 0) {
            throw new IllegalArgumentException();
        }
        tasks = new WaitablePriorityQueueCond<>();
        threads = new ArrayList<>(numOfThreads);
        setNumberOfThreads(numOfThreads);
    }

    @Override
    public void execute(Runnable command) {
        Objects.requireNonNull(command);
        submitImp(() -> {
            command.run();
            return null;
        }, DEFAULTPRIORITY);
    }

    public <T> Future<T> submit(Callable<T> callable, Priority priority) {
        return submitImp(callable, priority.ordinal());
    }

    public <T> Future<T> submit(Callable<T> callable) {
        return submitImp(callable, DEFAULTPRIORITY);
    }

    public Future<Void> submit(Runnable runnable, Priority priority) {
        Objects.requireNonNull(priority);
        Objects.requireNonNull(runnable);
        return submitImp(() -> {
            runnable.run();
            return null;
        }, priority.ordinal());
    }

    public Future<Void> submit(Runnable runnable) {
        Objects.requireNonNull(runnable);
        return submitImp(() -> {
            runnable.run();
            return null;
        }, DEFAULTPRIORITY);

    }

    public <T> Future<T> submit(Runnable runnable, Priority priority, T result) {
        Objects.requireNonNull(priority);
        Objects.requireNonNull(runnable);
        return submitImp(() -> {
            runnable.run();
            return result;
        }, priority.ordinal());
    }

    public void setNumberOfThreads(int numOfThreads) {
        int startSize = threads.size();
        if (numOfThreads >= startSize) {
            for (int i = 0; i < numOfThreads - startSize; ++i) {
                ThreadImp t = new ThreadImp();
                threads.add(t);
                t.start();
            }
        } else {
            for (int i = 0; i < startSize - numOfThreads; ++i) {
                submitImp(() -> {
                    ThreadImp currThreadImp = (ThreadImp) Thread.currentThread();
                    currThreadImp.isRunning = false;
                    threadPoolLock.lock();
                    try {
                        threads.remove(currThreadImp);
                    } finally {
                        threadPoolLock.unlock();
                    }
                    return null;
                }, SYSTEMPRIORITY);/* lowest to highest */
            }
        }
    }

    public void resume() {
        isPaused = false;
        threadPoolLock.lock();
        try {
            for (int i = 0; i < threads.size(); ++i) {
                threadPoolCond.signal();
                try {
                    Thread.sleep(80);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        } finally {
            threadPoolLock.unlock();
        }
    }

    public void pause() {
        isPaused = true;
        for (int i = 0; i < threads.size(); ++i) {
            submitImp(() -> {
                threadPoolLock.lock();
                try {
                    while (isPaused) {
                        threadPoolCond.await();
                    }
                } finally {
                    threadPoolLock.unlock();
                }
                return null;
            }, SYSTEMPRIORITY);
        }
    }

    public void awaitTermination() throws InterruptedException {
        awaitTermination(Long.MAX_VALUE, TimeUnit.HOURS);
    }

    public boolean awaitTermination(long timeout,
            TimeUnit unit)
            throws InterruptedException {
        return sema.tryAcquire(sizeBeforeShutdown, timeout, unit);
    }

    public void shutdown() {
        sizeBeforeShutdown = threads.size();
        for (int i = 0; i < sizeBeforeShutdown; ++i) {
            submitImp(() -> {
                ThreadImp currThreadImp = (ThreadImp) Thread.currentThread();
                currThreadImp.isRunning = false;
                threadPoolLock.lock();
                try {
                    threads.remove(currThreadImp);
                } finally {
                    threadPoolLock.unlock();
                }
                sema.release();
                return null;
            }, LOWESTPRIORITY);
        }
        isShutdown = true;
    }

    private <T> Future<T> submitImp(Callable<T> callable, int priority) {
        Future<T> future = null;
        if (!isShutdown) {
            Objects.requireNonNull(callable);
            Task<T> tempTask = new Task<>(callable, priority);
            tasks.enqueue(tempTask);
            future = tempTask.getFuture();
        }
        return future;
    }

    private <T> boolean removeTask(Task<T> task) {
        return tasks.remove(task);
    }

    private class ThreadImp extends Thread {
        private boolean isRunning = true;

        @Override
        public void run() {
            while (isRunning) {
                Task<?> currTask = tasks.dequeue();
                currTask.setThread();
                currTask.runTask();
            }
        }
    }

    private class Task<T> implements Comparable<Task<T>> {
        private final Callable<T> task;
        private final int priority;
        private final TaskFuture<T> taskFuture;
        private T result = null;
        private boolean isDone = false;
        private boolean isCancelled = false;

        private ReentrantLock lock = new ReentrantLock();
        private Condition cond = lock.newCondition();
        private Thread currentThread = null;

        public Task(Callable<T> callable, int priority) {
            task = callable;
            this.priority = priority;
            taskFuture = new TaskFuture<>();
        }

        public void runTask() {
            if (!isCancelled) {
                try {
                    result = task.call();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                futureUnlock();
                isDone = true;
            }
        }

        public Future<T> getFuture() {
            return taskFuture;
        }

        @Override
        public int compareTo(Task<T> other) {
            Objects.requireNonNull(other);
            return other.priority - priority;
        }

        private void futureUnlock() {
            lock.lock();
            try {
                cond.signal();
            } finally {
                lock.unlock();
            }
        }

        private void setThread() {
            this.currentThread = Thread.currentThread();
        }

        private class TaskFuture<E> implements Future<E> {

            @Override
            public boolean cancel(boolean mayInterruptIfRunning) {
                isCancelled = removeTask(Task.this);

                if (!isDone() && !isCancelled() && mayInterruptIfRunning && currentThread != null) {
                    isCancelled = true;
                    currentThread.interrupt();
                }
                isDone = true;
                return isCancelled();
            }

            @Override
            public boolean isCancelled() {
                return isCancelled;
            }

            @Override
            public boolean isDone() {
                return isDone;
            }

            @Override
            public E get() throws InterruptedException, ExecutionException {
                E val = null;
                try {
                    val = get(Long.MAX_VALUE, TimeUnit.HOURS);
                } catch (TimeoutException e) {
                    e.printStackTrace();
                }
                return val;
            }

            @Override
            public E get(long timeout, TimeUnit unit)
                    throws InterruptedException, ExecutionException, TimeoutException {
                lock.lock();
                try {
                    if (!isDone()) {
                        if (!cond.await(timeout, unit)) {
                            throw new TimeoutException();
                        }
                    }
                    if (isCancelled()) {
                        throw new CancellationException();
                    }
                } finally {
                    lock.unlock();
                }
                @SuppressWarnings("unchecked")
                E res = (E) result;
                return res;
            }

        }
    }

}
