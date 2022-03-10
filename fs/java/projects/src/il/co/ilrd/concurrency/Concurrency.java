package il.co.ilrd.concurrency;

import java.io.IOException;

public class Concurrency {
    public static void main(String[] args) {
        MyThread t = new MyThread();
        t.start();

        MyRunnable mr = new MyRunnable();
        Thread t2 = new Thread(mr);
        t2.start();

        t.interrupt();
        t2.interrupt();

    }
}

class MyRunnable implements Runnable {
    public void run() {
        ProcessBuilder builder = new ProcessBuilder("notepad++.exe");

        while (!Thread.currentThread().isInterrupted()) {
            try {
                Thread.sleep(1000);
                builder.start();

                System.out.println("ds");
            } catch (IOException e) {
                Thread.currentThread().interrupt();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class MyThread extends Thread {
    public void run() {
        ProcessBuilder builder = new ProcessBuilder("notepad.exe");

        while (!currentThread().isInterrupted()) {
            try {
                builder.start();

                System.out.println("ds");
            } catch (IOException e) {
                currentThread().interrupt();
            }
        }

    }
}