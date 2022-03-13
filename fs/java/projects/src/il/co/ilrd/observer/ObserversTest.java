package il.co.ilrd.observer;

class Observer1 {
    private final int DEFAULTNUM = 0;
    private int num = DEFAULTNUM;
    private Callback<Integer> callback = new Callback<>(x -> System.out.println(++this.num), () -> num = DEFAULTNUM);

    public void register(Subject subject) {
        subject.registerObserver(callback);
    }
}

class Observer2 {
    private final int DEFAULTNUM = 10;
    private int num = DEFAULTNUM;
    private Callback<Integer> callback = new Callback<>(x -> System.out.println(++this.num), () -> num = DEFAULTNUM);

    public void register(Subject subject) {
        subject.registerObserver(callback);
    }
}

class Observer3 {
    private final int DEFAULTNUM = 100;
    private int num = DEFAULTNUM;
    private Callback<Integer> callback = new Callback<>(x -> System.out.println(++this.num), () -> num = DEFAULTNUM);

    public void register(Subject subject) {
        subject.registerObserver(callback);
    }

}

class Subject {
    Dispatcher<Integer> dispatcher = new Dispatcher<>();

    public void registerObserver(Callback<Integer> callback) {
        dispatcher.register(callback);
    }

    public void unregisterObserver(Callback<Integer> callback) {
        dispatcher.unregister(callback);
    }
}

class Main {
    public static void main(String[] args) {
        Subject subject = new Subject();
        Observer1 o1 = new Observer1();
        o1.register(subject);
    }
}