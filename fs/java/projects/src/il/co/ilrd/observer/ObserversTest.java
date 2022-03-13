package il.co.ilrd.observer;

class Observer {

    public void register(Subject subject) {

    }
}

class Subject {

    public void registerObserver(Callback<String> callback) {

    }

    public void unregisterObserver(Callback<String> callback) {

    }
}