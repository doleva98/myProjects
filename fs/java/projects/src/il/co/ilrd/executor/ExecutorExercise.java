package il.co.ilrd.executor;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

public class ExecutorExercise {
    public static void ex1() {
        ExecutorService executor = Executors.newSingleThreadExecutor();
        Callable<String> callableTask = new Callable<String>() {
            @Override
            public String call() throws Exception {
                return "hello world";
            }

        };

        Future<String> future = executor.submit(callableTask);
        try {
            System.out.println(future.get());
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
        executor.shutdown();
        try {
            if (!executor.awaitTermination(800, TimeUnit.MILLISECONDS)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
        }
    }

    public static void singleThreadPool() {
        ExecutorService executor = Executors.newSingleThreadExecutor();
        Callable<String> callableTask = () -> "hello world";
        List<Future<String>> list_future = new ArrayList<>();
        for (int i = 0; i < 5; ++i) {
            list_future.add(executor.submit(callableTask));
        }
        list_future.forEach(future -> {
            try {
                System.out.println(future.get());
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            } catch (ExecutionException e1) {
                e1.printStackTrace();
            }
        });

        executor.shutdown();
        try {
            if (!executor.awaitTermination(800, TimeUnit.MILLISECONDS)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
        }
    }

    public static void fixedSizedPool3Threads() {
        ExecutorService executor = Executors.newFixedThreadPool(3);
        Callable<String> callableTask = () -> "hello world";
        List<Future<String>> list_future = new ArrayList<>();
        for (int i = 0; i < 5; ++i) {
            list_future.add(executor.submit(callableTask));
        }

        list_future.forEach(future -> {
            try {
                System.out.println(future.get());
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            } catch (ExecutionException e1) {
                e1.printStackTrace();
            }
        });

        executor.shutdown();
        try {
            if (!executor.awaitTermination(800, TimeUnit.MILLISECONDS)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
        }
    }

    public static void cachedThreadPool() {
        ExecutorService executor = Executors.newCachedThreadPool();
        Callable<String> callableTask = () -> "hello world";
        List<Future<String>> list_future = new ArrayList<>();
        for (int i = 0; i < 5; ++i) {
            list_future.add(executor.submit(callableTask));
        }

        list_future.forEach(future -> {
            try {
                System.out.println(future.get());
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            } catch (ExecutionException e1) {
                e1.printStackTrace();
            }
        });

        executor.shutdown();
        try {
            if (!executor.awaitTermination(800, TimeUnit.MILLISECONDS)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
        }
    }

    public static void scheduledThreadPool() {
        ScheduledExecutorService executor = Executors.newSingleThreadScheduledExecutor();
        Callable<String> callableTask = () -> "hello world";
        List<Future<String>> list_future = new ArrayList<>();
        for (int i = 0; i < 5; ++i) {
            list_future.add(executor.schedule(callableTask, 3, TimeUnit.SECONDS));
        }

        list_future.forEach(future -> {
            try {
                System.out.println(future.get());
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            } catch (ExecutionException e1) {
                e1.printStackTrace();
            }
        });

        executor.shutdown();
        try {
            if (!executor.awaitTermination(800, TimeUnit.MILLISECONDS)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
        }
    }

    public static void scheduledTestThreadPool() {
        ScheduledExecutorService executor = Executors.newSingleThreadScheduledExecutor();
        Runnable runnableTask = () -> System.out.println("hello world");
        List<ScheduledFuture<?>> list_future = new ArrayList<>();
        for (int i = 0; i < 5; ++i) {
            list_future.add(executor.scheduleAtFixedRate(runnableTask, 1, 3, TimeUnit.SECONDS));
        }
        try {
            Thread.sleep(9000);
        } catch (InterruptedException e1) {
            e1.printStackTrace();
        }
        list_future.forEach(future -> {
            future.cancel(true);
        });

        executor.shutdown();
        try {
            if (!executor.awaitTermination(800, TimeUnit.MILLISECONDS)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
        }
    }

    public static void main(String[] args) {
        /* ex1();
        singleThreadPool(); */
        // fixedSizedPool3Threads();
        // cachedThreadPool();
        scheduledThreadPool();
        // scheduledTestThreadPool();
    }
}