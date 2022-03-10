package il.co.ilrd.factory;

import java.util.function.Function;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class Factory<T, D, K> {
    private Map<K, Function<D, ? extends T>> factoryImpl = new HashMap<>();

    // Function<T, R>
    // T – Type of the input to the function.
    // R – Type of the result of the function.

    public void add(K key, Function<D, ? extends T> func) {
        Objects.requireNonNull(key);
        Objects.requireNonNull(func);
        factoryImpl.put(key, func);
    }

    public T create(K key) {
        return create(key, null);
    }

    public T create(K key, D data) {
        Objects.requireNonNull(key);
        return factoryImpl.get(key).apply(data);
    }
}