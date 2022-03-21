package il.co.ilrd.threadpool;

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

    @Test
    public void cancelInterruptTest() {
        ThreadPoolIMP poolThread = new ThreadPoolIMP(2);
        Future<Long> taskFuture = poolThread.submit(() -> {
            System.out.println("hello");
            Thread.sleep(5000);
            System.out.println("bye");
            return Long.valueOf(3);
        });
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e1) {
            e1.printStackTrace();
        }
        taskFuture.cancel(true);
        try {
            taskFuture.get();
            taskFuture.get(1, TimeUnit.SECONDS);
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        } catch (TimeoutException e) {
            e.printStackTrace();
        }

    }
}
