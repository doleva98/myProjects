package il.co.ilrd.iosystem;

import java.io.Serializable;

public interface CRUD<K extends Serializable, D extends Serializable> extends AutoCloseable {
    K create(D data);

    D read(K key);

    void update(K key, D data);

    void delete(K key);
}
