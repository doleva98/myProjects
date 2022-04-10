package il.co.java_quizzes.singletonFactory;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.function.Function;

public class SingletonFactory<K, D, T> {
    private Map<K, Function<D, T>> factoryImpl = new HashMap<>();

    private SingletonFactory() {

    }

    public void add(K key, Function<D, T> recipe) {
        Objects.requireNonNull(key);/* null is not a valid key */
        Objects.requireNonNull(recipe);
        factoryImpl.put(key, recipe);
    }

    public T create(K key, D data) {
        Objects.requireNonNull(key);
        return factoryImpl.get(key).apply(data);
    }

    /*   private static class Holder {
        private static final SingletonFactory obj = new SingletonFactory<>();
    }
    
    public static <K, D, T> SingletonFactory<K, D, T> getInstance() {
        return Holder.obj;
    } */
}
