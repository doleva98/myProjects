package il.co.ilrd.threadpool;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

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

        Future<Void> f3 = threadPool.submit(() -> {
            for (int i = 0; i < 3; ++i) {
            }
        });

        try {
            assertNull(f3.get());
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }

        Future<Void> f4 = threadPool.submit(() -> {
            for (int i = 0; i < 3; ++i) {
            }
        }, Priority.HIGH);

        try {
            assertNull(f4.get());
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }

        Future<String> f5 = threadPool.submit(() -> {
            for (int i = 0; i < 3; ++i) {
            }
        }, Priority.HIGH, "hello world");

        try {
            assertEquals(f5.get(61, TimeUnit.SECONDS), "hello world");
        } catch (InterruptedException | ExecutionException | TimeoutException e) {
            e.printStackTrace();
        }
    }
}
