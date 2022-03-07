package il.co.ilrd.test;

class Test extends Thread {
    public static Object cacheLock = new Object();

    public static void main(String[] args) {
        throw new RuntimeException();

    }
}