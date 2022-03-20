package il.co.ilrd.threadpool;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.CancellationException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import il.co.ilrd.waitablepq.WaitablePriorityQueueCond;

public class ThreadPoolIMP implements Executor {
    public enum Priority {
        LOW,
        MEDIUM,
        HIGH;
    }

    private WaitablePriorityQueueCond<Task<?>> tasks;
    private List<ThreadImp> threads;

    public ThreadPoolIMP(int numOfThreads) {
        tasks = new WaitablePriorityQueueCond<>();
        threads = new ArrayList<>();
    }

    @Override
    public void execute(Runnable command) {
        threads.forEach(thread -> thread.run());
    }

    public <T> Future<T> submit(Callable<T> callable, Priority priority) {
        return submitImp(callable, priority.ordinal());
    }

    public <T> Future<T> submit(Callable<T> callable) {
        return submitImp(callable, 1);
    }

    public Future<Void> submit(Runnable runnable, Priority priority) {
        return submitImp(() -> {
            runnable.run();
            return null;
        }, priority.ordinal());
    }

    public Future<Void> submit(Runnable runnable) {
        return submitImp(() -> {
            runnable.run();
            return null;
        }, 1);

    }

    public <T> Future<T> submit(Runnable runnable, Priority priority, T result) {
        return submitImp(() -> {
            runnable.run();
            return result;
        }, priority.ordinal());
    }

    private <T> Future<T> submitImp(Callable<T> callable, int priority) {
        Task<T> tempTask = new Task<>(callable, priority);
        tasks.enqueue(tempTask);
        return tempTask.getFuture();
    }

    private class ThreadImp implements Runnable {

        @Override
        public void run() {
            while (true) {
                tasks.dequeue().runTask();
            }
        }
    }

    private class Task<T> implements Comparable<Task<T>> {
        private final Callable<T> task;
        private final int priority;
        private final TaskFuture<T> taskFuture;
        private T result = null;

        public Task(Callable<T> callable, int priority) {
            task = callable;
            this.priority = priority;
            taskFuture = new TaskFuture<>();
        }

        public void runTask() {
            try {
                result = task.call();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        public Future<T> getFuture() {
            return taskFuture;
        }

        @Override
        public int compareTo(Task<T> other) {
            return priority - other.priority;
        }

        private class TaskFuture<E> implements Future<E> {

            @Override
            public boolean cancel(boolean mayInterruptIfRunning) {
                return false;
            }

            @Override
            public boolean isCancelled() {
                // TODO Auto-generated method stub
                return false;
            }

            @Override
            public boolean isDone() {
                // TODO Auto-generated method stub
                return false;
            }

            @Override
            public E get() throws InterruptedException, ExecutionException {
                if (isCancelled()) {
                    throw new CancellationException();
                }
                return result;
            }

            @Override
            public E get(long timeout, TimeUnit unit)
                    throws InterruptedException, ExecutionException, TimeoutException {
                // TODO Auto-generated method stub
                return null;
            }

        }

    }

}
