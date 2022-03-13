package il.co.ilrd.observer;

import java.util.Objects;
import java.util.function.Consumer;

public class Callback<T> {

    private Dispatcher<T> dispatcher;
    @SuppressWarnings("unused")
    private Consumer<T> update;
    @SuppressWarnings("unused")
    private Runnable stopService;

    public Callback(Consumer<T> update, Runnable stopService) {
        Objects.requireNonNull(update);
        Objects.requireNonNull(stopService);
        this.update = update;
        this.stopService = stopService;
    }

    public void update(T data) {
        update(data);
    }

    public void stopService() {
        stopService();
    }

    public void setDispatcher(Dispatcher<T> dispatcher) {
        Objects.requireNonNull(dispatcher);
        this.dispatcher = dispatcher;
    }

    public void unregister() {
        if (dispatcher == null) {
            System.err.println("ERROR no dispatcher");
        }
        dispatcher.unregister(this);
    }

    public void setUpdate(Consumer<T> update) {
        Objects.requireNonNull(update);
        this.update = update;
    }

    public void setStopService(Runnable stopService) {
        Objects.requireNonNull(stopService);
        this.stopService = stopService;
    }
}