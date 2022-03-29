package il.co.ilrd.iosystem;

import java.io.IOException;

public interface CRUD<K, D> extends AutoCloseable {
    K create(D data) throws IOException;

    D read(K key) throws IOException, ClassNotFoundException;

    void update(K key, D data) throws IOException, ClassNotFoundException;

    void delete(K key) throws IOException, ClassNotFoundException;
}
