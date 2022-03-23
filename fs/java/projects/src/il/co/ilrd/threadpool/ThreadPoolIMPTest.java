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
    public void awaitTerminationTest() {
        ThreadPoolIMP threadPool = new ThreadPoolIMP(13);
        threadPool.shutdown();
        try {
            assertTrue(threadPool.awaitTermination(3, TimeUnit.HOURS));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        ThreadPoolIMP threadPool2 = new ThreadPoolIMP(10);
        threadPool2.submit(() -> {
            @SuppressWarnings("unused")
            int i = 0;
            while (true) {
                ++i;
            }
        }, Priority.HIGH);
        try {
            Thread.sleep(800);
        } catch (InterruptedException e1) {
            e1.printStackTrace();
        }
        threadPool2.shutdown();
        try {
            assertFalse(threadPool2.awaitTermination(80, TimeUnit.MILLISECONDS));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        ThreadPoolIMP threadPool3 = new ThreadPoolIMP(10);
        threadPool3.submit(() -> {
        }, Priority.HIGH);
        try {
            Thread.sleep(800);
        } catch (InterruptedException e1) {
            e1.printStackTrace();
        }
        threadPool3.shutdown();
        try {
            assertTrue(threadPool3.awaitTermination(80, TimeUnit.MILLISECONDS));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

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
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        assertFalse(f.cancel(false));
        assertFalse(f.cancel(true));
    }

    @Test
    public void hardCheck() {
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

    @Test
    public void checkSetNumber() {
        ThreadPoolIMP threadPool = new ThreadPoolIMP(10);
        List<Future<Integer>> listFuture = new ArrayList<>();
        final int SIZE = 50;
        Callable<Integer> callable = () -> {
            int j = 0;
            Thread.sleep(50);
            return j;
        };
        for (int i = 0; i < SIZE; ++i) {
            listFuture.add(threadPool.submit(callable));
            listFuture.add(threadPool.submit(callable, Priority.LOW));
            listFuture.add(threadPool.submit(callable, Priority.MEDIUM));
            listFuture.add(threadPool.submit(callable, Priority.HIGH));
        }
        threadPool.setNumberOfThreads(50);
        for (int i = 0; i < SIZE; ++i) {
            listFuture.add(threadPool.submit(callable));
            listFuture.add(threadPool.submit(callable, Priority.LOW));
            listFuture.add(threadPool.submit(callable, Priority.MEDIUM));
            listFuture.add(threadPool.submit(callable, Priority.HIGH));
        }
        listFuture.forEach((future) -> {
            try {
                assertEquals(future.get(), 0);
                try {
                    assertEquals(future.get(59, TimeUnit.SECONDS), 0);
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

    @Test
    public void checkSetNumber2() {
        ThreadPoolIMP threadPool = new ThreadPoolIMP(10);
        List<Future<Integer>> listFuture = new ArrayList<>();
        final int SIZE = 50;
        Callable<Integer> callable = () -> {
            int j = 0;
            Thread.sleep(50);
            return j;
        };
        for (int i = 0; i < SIZE; ++i) {
            listFuture.add(threadPool.submit(callable));
            listFuture.add(threadPool.submit(callable, Priority.LOW));
            listFuture.add(threadPool.submit(callable, Priority.MEDIUM));
            listFuture.add(threadPool.submit(callable, Priority.HIGH));
        }
        threadPool.setNumberOfThreads(1);
        for (int i = 0; i < SIZE; ++i) {
            listFuture.add(threadPool.submit(callable));
            listFuture.add(threadPool.submit(callable, Priority.LOW));
            listFuture.add(threadPool.submit(callable, Priority.MEDIUM));
            listFuture.add(threadPool.submit(callable, Priority.HIGH));
        }
        listFuture.forEach((future) -> {
            try {
                assertEquals(future.get(), 0);
                try {
                    assertEquals(future.get(59, TimeUnit.SECONDS), 0);
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

    @Test
    public void checkSetNumber3() {
        ThreadPoolIMP threadPool = new ThreadPoolIMP(10);
        List<Future<Integer>> listFuture = new ArrayList<>();
        final int SIZE = 50;
        Callable<Integer> callable = () -> {
            int j = 0;
            System.out.println("hello world");
            Thread.sleep(500);
            return j;
        };
        threadPool.pause();
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        threadPool.resume();
        for (int i = 0; i < SIZE; ++i) {
            listFuture.add(threadPool.submit(callable));
            listFuture.add(threadPool.submit(callable, Priority.LOW));
            listFuture.add(threadPool.submit(callable, Priority.MEDIUM));
            listFuture.add(threadPool.submit(callable, Priority.HIGH));
        }

        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        listFuture.forEach((future) -> {
            try {
                assertEquals(future.get(), 0);
                try {
                    assertEquals(future.get(59, TimeUnit.SECONDS), 0);
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

    @Test
    public void checkSetNumber4() {
        ThreadPoolIMP threadPool = new ThreadPoolIMP(10);
        List<Future<Void>> listFuture = new ArrayList<>();
        final int SIZE = 10;
        Callable<Void> callable = () -> {
            for (int i = 0; i < SIZE; ++i) {
                System.out.println("fd");
            }
            return null;
        };
        threadPool.pause();
        for (int i = 0; i < SIZE; ++i) {
            listFuture.add(threadPool.submit(callable));
        }
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        threadPool.resume();
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        threadPool.shutdown();
    }

}
