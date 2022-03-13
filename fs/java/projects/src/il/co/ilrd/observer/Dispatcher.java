package il.co.ilrd.observer;

import java.util.ArrayList;
import java.util.Collection;

public class Dispatcher<T> {

    private Collection<Callback<T>> callbackList = new ArrayList<>();

    public void notifyAllCallback(T data) {
        callbackList.forEach(data -> update);
    }

    public void stopAllCallback() {
    }

    public void register(Callback<T> callback) {
    }

    public void unregister(Callback<T> callback) {
    }
}