package il.co.ilrd.concurrency;

import java.io.IOException;

public class Concurrency {
    public static void main(String[] args) {
        MyThread t = new MyThread();
        t.start();

        MyRunnable mr = new MyRunnable();
        Thread t2 = new Thread(mr);
        t2.start();

    }
}

class MyRunnable implements Runnable {
    public void run() {
        ProcessBuilder builder = new ProcessBuilder("notepad++.exe");
        Process pro;
        try {
            pro = builder.start();
            Thread.sleep(5000);
            pro.wait();
            System.out.println("ds");
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

    }
}

class MyThread extends Thread {
    public void run() {
        ProcessBuilder builder = new ProcessBuilder("notepad.exe");
        Process pro;
        try {
            pro = builder.start();
            sleep(5000);
            pro.wait();
            System.out.println("ds");
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

    }
}