/* yoni */
package il.co.ilrd.observer;

class Observer1 {
    private final int DEFAULTNUM = 0;
    private int num = DEFAULTNUM;
    private Callback<Integer> callback = new Callback<>(x -> System.out.println(num += x),
            () -> System.out.println(num = DEFAULTNUM));

    public void register(Subject subject) {
        subject.registerObserver(callback);
    }

    public void setUpdate() {
        callback.setUpdate(x -> System.out.println(num += x * 2));
    }

    public void setStopService() {
        callback.setStopService(() -> System.out.println(num = 1502564546));
    }
}

class Observer2 {
    private final int DEFAULTNUM = 10;
    private int num = DEFAULTNUM;
    private Callback<Integer> callback = new Callback<>(x -> System.out.println(num += x),
            () -> System.out.println(num = DEFAULTNUM));

    public void register(Subject subject) {
        subject.registerObserver(callback);
    }
}

class Observer3 {
    private final int DEFAULTNUM = 100;
    private int num = DEFAULTNUM;
    private Callback<Integer> callback = new Callback<>(x -> System.out.println(num += x),
            () -> System.out.println(num = DEFAULTNUM));

    public void register(Subject subject) {
        subject.registerObserver(callback);
    }

    public void unregister(Subject subject) {
        subject.unregisterObserver(callback);
    }

}

class Subject {
    private Dispatcher<Integer> dispatcher = new Dispatcher<>();

    public void registerObserver(Callback<Integer> callback) {
        dispatcher.register(callback);
    }

    public void unregisterObserver(Callback<Integer> callback) {
        dispatcher.unregister(callback);
    }

    public void notifyAllCallback() {
        dispatcher.notifyAllCallback(5);
    }

    public void stopAllCallback() {
        dispatcher.stopAllCallback();
    }
}

class Main {
    public static void main(String[] args) {
        Subject subject = new Subject();
        Observer1 o1 = new Observer1();
        o1.register(subject);
        Observer2 o2 = new Observer2();
        o2.register(subject);
        Observer3 o3 = new Observer3();
        o3.register(subject);

        subject.notifyAllCallback();
        subject.notifyAllCallback();
        subject.notifyAllCallback();

        System.out.println("stopping all observers");
        subject.stopAllCallback();

        System.out.println("removing o3");
        o3.unregister(subject);
        o3 = null;

        o1.setUpdate();
        o1.setStopService();

        subject.notifyAllCallback();
        subject.notifyAllCallback();
        subject.notifyAllCallback();

        subject.stopAllCallback();

    }
}