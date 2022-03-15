package il.co.ilrd.observer;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Objects;

public class Dispatcher<T> {

    private Collection<Callback<T>> callbackList = new ArrayList<>();

    public void notifyAllCallback(T data) {
        callbackList.forEach(callback -> callback.update(data));
    }

    public void stopAllCallback() {
        callbackList.forEach(callback -> callback.stopService());
    }

    public void register(Callback<T> callback) {
        Objects.requireNonNull(callback);
        callbackList.add(callback);
        callback.setDispatcher(this);
    }

    public void unregister(Callback<T> callback) {
        Objects.requireNonNull(callback);
        callback.stopService();
        callbackList.remove(callback);
    }
}