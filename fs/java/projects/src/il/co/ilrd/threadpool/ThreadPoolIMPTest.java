package il.co.ilrd.threadpool;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import org.junit.jupiter.api.Test;

import il.co.ilrd.threadpool.ThreadPoolIMP.Priority;

public class ThreadPoolIMPTest {
    @Test
    public void basicTest() {
        ThreadPoolIMP threadPool = new ThreadPoolIMP(3);

        Future<Integer> f1 = threadPool.submit(() -> {
            int j = 0;
            for (int i = 0; i < 50; ++i) {
                j += 2;
            }
            return j;
        }, Priority.LOW);

        try {
            assertEquals(f1.get(), 100);
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
        assertTrue(f1.isDone());
        assertFalse(f1.isCancelled());

        Future<Integer> f2 = threadPool.submit(() -> {
            int j = 0;
            for (int i = 0; i < 50; ++i) {
                j += 3;
            }
            return j;
        });

        try {
            assertEquals(f2.get(6, TimeUnit.SECONDS), 150);
        } catch (InterruptedException | ExecutionException | TimeoutException e) {
            e.printStackTrace();
        }
        assertTrue(f2.isDone());
        assertFalse(f2.isCancelled());

        Future<Void> f3 = threadPool.submit(() -> {
            for (int i = 0; i < 3; ++i) {
            }
        });

        try {
            assertNull(f3.get());
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
        assertTrue(f3.isDone());
        assertFalse(f3.isCancelled());

        Future<Void> f4 = threadPool.submit(() -> {
            for (int i = 0; i < 3; ++i) {
            }
        }, Priority.HIGH);

        try {
            assertNull(f4.get());
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
        assertTrue(f4.isDone());
        assertFalse(f4.isCancelled());

        Future<String> f5 = threadPool.submit(() -> {
            for (int i = 0; i < 3; ++i) {
            }
        }, Priority.HIGH, "hello world");

        try {
            assertEquals(f5.get(61, TimeUnit.SECONDS), "hello world");
        } catch (InterruptedException | ExecutionException | TimeoutException e) {
            e.printStackTrace();
        }
        assertTrue(f5.isDone());
        assertFalse(f5.isCancelled());
    }

    @Test
    public void cancelCheck() {
        ThreadPoolIMP threadPool = new ThreadPoolIMP(10);
        Future<Integer> f = threadPool.submit(() -> {
            int j = 0;
            for (int i = 0; i < 50; ++i) {
                j += 3;
            }
            return j;
        });

        try {
            assertEquals(f.get(), 150);
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
        assertFalse(f.cancel(false));
        assertFalse(f.cancel(true));
    }

    @Test
    public void hardCheck(){
        ThreadPoolIMP threadPool = new ThreadPoolIMP(10);
        List<Future<Integer>> listFuture = new ArrayList<>();
        final int SIZE = 50;
        Callable<Integer> callable = () -> {
            int j = 0;
            for (int i = 0; i < SIZE; ++i) {
                j += 3;
            }
            return j;
        };
        for (int i = 0; i < SIZE; ++i) {
            listFuture.add(threadPool.submit(callable));
            listFuture.add(threadPool.submit(callable, Priority.LOW));
            listFuture.add(threadPool.submit(callable, Priority.MEDIUM));
            listFuture.add(threadPool.submit(callable, Priority.HIGH));
        }
        listFuture.forEach((future) -> {
            try {
                assertEquals(future.get(), 150);
                try {
                    assertEquals(future.get(59, TimeUnit.SECONDS), 150);
                } catch (TimeoutException e) {
                    e.printStackTrace();
                }
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
            assertTrue(future.isDone());
            assertFalse(future.isCancelled());

        });
    }
}
