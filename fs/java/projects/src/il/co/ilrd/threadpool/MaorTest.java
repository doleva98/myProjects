package il.co.ilrd.threadpool;

import java.util.concurrent.CancellationException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import org.junit.Test;

public class MaorTest {
    static int counter = 0;

    @Test
    public void cancelTest() throws InterruptedException {
        ThreadPoolIMP poolThread = new ThreadPoolIMP(2);
        Future<Long> taskFuture = poolThread.submit(() -> Long.valueOf(1));
        Thread.sleep(1000);
        taskFuture.cancel(false);
        assert (!taskFuture.isCancelled());
        assert (taskFuture.isDone());
    }

    @Test(expected = CancellationException.class)
    public void cancelInterruptTest() {
        ThreadPoolIMP poolThread = new ThreadPoolIMP(2);
        Future<Long> taskFuture = poolThread.submit(() -> {
            System.out.println("hello");
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e1) {
                System.err.println("it is ok");
            }
            System.out.println("bye");
            return Long.valueOf(3);
        });
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e1) {
            System.err.println("it is ok");
        }
        taskFuture.cancel(true);
        try {
            taskFuture.get();
            taskFuture.get(1, TimeUnit.SECONDS);
        } catch (InterruptedException | TimeoutException | ExecutionException e) {
            e.printStackTrace();
        }

    }

    @Test
    public void testPauseAndResume() {
        final int NUM_OF_THREADS = 2;
        ThreadPoolIMP threadPool = new ThreadPoolIMP(NUM_OF_THREADS);

        Runnable taskRunnable = new Runnable() {
            @Override
            public void run() {
                System.err.println("Task " + Thread.currentThread().getName() + " started");
                for (int i = 0; i < 5; ++i) {
                    System.err.println("Task " + Thread.currentThread().getName() + ": " + i);
                }
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };
        System.err.println("before submit");
        for (int i = 0; i < 10 * NUM_OF_THREADS; i++) {
            threadPool.submit(taskRunnable);
        }
        System.err.println("after submit");
        threadPool.pause();

        System.err.println("Threadpool paused");

        try {
            Thread.sleep(5000);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        threadPool.resume();

        try {
            Thread.sleep(10000);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }
}
