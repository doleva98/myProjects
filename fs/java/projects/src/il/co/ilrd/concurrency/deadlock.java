package il.co.ilrd.concurrency;

class Test extends Thread {
    public static final Object cacheLock = new Object();
    public static final Object tableLock = new Object();

    public static void main(String[] args) {
        Test t = new Test();
        Test.TestInner t2 = t.new TestInner();
        t2.start();
        t.start();

        try {
            t.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        f1();
    }

    public void f1() {
        synchronized (tableLock) {
            try {
                sleep(1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            synchronized (cacheLock) {
                System.out.println("hello");
            }
        }
    }

    class TestInner extends Thread {
        public void f2() {
            synchronized (cacheLock) {
                try {
                    sleep(1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                synchronized (tableLock) {
                    System.out.println("hello");
                }
            }
        }

        public void run() {
            f2();
        }
    }
}