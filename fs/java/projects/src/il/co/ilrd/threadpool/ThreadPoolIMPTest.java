package il.co.ilrd.threadpool;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import il.co.ilrd.threadpool.ThreadPoolIMP.Priority;

public class ThreadPoolIMPTest {
    public static void main(String[] args) {
        ThreadPoolIMP threadPool = new ThreadPoolIMP(3);

        Future<Integer> f1 = threadPool.submit(() -> {
            int j = 0;
            for (int i = 0; i < 50; ++i) {
                j += 2;
            }
            return j;
        }, Priority.LOW);

        try {
            System.out.println(f1.get());
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
            System.out.println(f2.get(6, TimeUnit.SECONDS));
        } catch (InterruptedException | ExecutionException | TimeoutException e) {
            e.printStackTrace();
        }

        Future<Void> f3 = threadPool.submit(() -> {
            for (int i = 0; i < 3; ++i) {
                sysou   
            }
        });

        try {
            System.out.println(f3.get(16, TimeUnit.SECONDS));
        } catch (InterruptedException | ExecutionException | TimeoutException e) {
            e.printStackTrace();
        }

    }
}
