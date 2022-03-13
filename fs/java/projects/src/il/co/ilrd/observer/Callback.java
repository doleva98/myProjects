/* yoni */
package il.co.ilrd.observer;

import java.util.Objects;
import java.util.function.Consumer;

public class Callback<T> {

    private Dispatcher<T> dispatcher;
    private Consumer<T> updateService;
    private Runnable stopFunction;

    public Callback(Consumer<T> updateService, Runnable stopFunction) {
        Objects.requireNonNull(updateService);
        Objects.requireNonNull(stopFunction);
        this.updateService = updateService;
        this.stopFunction = stopFunction;
    }

    public void update(T data) {
        updateService.accept(data);
    }

    public void stopService() {
        stopFunction.run();
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

    public void setUpdate(Consumer<T> updateService) {
        Objects.requireNonNull(updateService);
        this.updateService = updateService;
    }

    public void setStopService(Runnable stopFunction) {
        Objects.requireNonNull(stopFunction);
        this.stopFunction = stopFunction;
    }
}