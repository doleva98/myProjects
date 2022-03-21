package il.co.ilrd.threadpool;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.Callable;
import java.util.concurrent.CancellationException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Future;
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

    private WaitablePriorityQueueCond<Task<?>> tasks;
    private List<ThreadImp> threads;

    private final static int DEFAULTPRIORITY = Priority.MEDIUM.ordinal();

    public ThreadPoolIMP(int numOfThreads) {
        if (numOfThreads <= 0) {
            throw new IllegalArgumentException();
        }
        tasks = new WaitablePriorityQueueCond<>();
        threads = new ArrayList<>(numOfThreads);
        for (int i = 0; i < numOfThreads; ++i) {
            ThreadImp t = new ThreadImp();
            threads.add(t);
            t.thread.start();
        }
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
        return submitImp(() -> {
            runnable.run();
            return null;
        }, priority.ordinal());
    }

    public Future<Void> submit(Runnable runnable) {
        return submitImp(() -> {
            runnable.run();
            return null;
        }, DEFAULTPRIORITY);

    }

    public <T> Future<T> submit(Runnable runnable, Priority priority, T result) {
        Objects.requireNonNull(priority);
        return submitImp(() -> {
            runnable.run();
            return result;
        }, priority.ordinal());
    }

    public void setNumberOfThreads(int numOfThreads) {

    }

    public void resume() {
    }

    public void pause() {
    }

    public void awaitTermination() throws InterruptedException {

    }

    public boolean awaitTermination(long timeout,
            TimeUnit unit)
            throws InterruptedException {
        return true;
    }

    public void shutdown() {
    }

    private <T> Future<T> submitImp(Callable<T> callable, int priority) {
        Objects.requireNonNull(callable);
        Task<T> tempTask = new Task<>(callable, priority);
        tasks.enqueue(tempTask);
        return tempTask.getFuture();
    }

    private <T> boolean removeTask(Task<T> task) {
        return tasks.remove(task);
    }

    private class ThreadImp implements Runnable {
        private Thread thread = new Thread(this);

        @Override
        public void run() {
            while (true) {
                Task<?> currTask = tasks.dequeue();
                currTask.runTask();
                currTask.setThread();
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
            return priority - other.priority;
        }

        private void futureUnlock() {
            lock.lock();
            try {
                cond.signal();
            } finally {
                lock.unlock();
            }
        }

        public void setThread() {
            this.currentThread = Thread.currentThread();
        }

        private class TaskFuture<E> implements Future<E> {

            @Override
            public boolean cancel(boolean mayInterruptIfRunning) {
                if (!isDone() && !isCancelled() && mayInterruptIfRunning && currentThread != null) {
                    currentThread.interrupt();
                    isCancelled = true;
                }
                isCancelled = removeTask(Task.this);
                isDone = true;
                return isCancelled;
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
                if (isCancelled) {
                    throw new CancellationException();
                }
                lock.lock();
                try {
                    if (!isDone()) {
                        cond.await(timeout, unit);
                    }
                    if (isCancelled()) {
                        throw new CancellationException();
                    }
                    if (!isDone()) {
                        throw new TimeoutException();
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
