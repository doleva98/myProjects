package il.co.ilrd.iosystem;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Stack;

class FileCRUD implements CRUD<Integer, String> {
    private FileInputStream fis = null;
    private FileOutputStream fos = null;
    private ObjectOutputStream oos = null;
    private ObjectInputStream ois = null;

    private Stack<String> stack = new Stack<>();

    private int size = 0;

    public FileCRUD(String path) throws IOException, ClassNotFoundException {
        fos = new FileOutputStream(path);
        fis = new FileInputStream(path);
        oos = new ObjectOutputStream(fos);
        ois = new ObjectInputStream(fis);

        while (ois.available() != 0) {
            stack.push((String) ois.readObject());
            ++size;
        }
        while (!stack.isEmpty()) {
            oos.writeObject(stack.pop());
        }
    }

    @Override
    public void close() throws Exception {
        fis.close();
        fos.close();
        oos.close();
        ois.close();
    }

    @Override
    public Integer create(String data) throws IOException {
        oos.writeObject(data);
        return size++;
    }

    @Override
    public String read(Integer key) throws IOException, ClassNotFoundException {
        if (key >= size || key < 0) {
            throw new IOException();
        }
        for (int i = size - 1; i > key; --i) {
            stack.push((String) ois.readObject());
        }
        String result = (String) ois.readObject();
        oos.writeObject(result);
        while (!stack.isEmpty()) {
            oos.writeObject(stack.pop());
        }
        return result;
    }

    @Override
    public void update(Integer key, String data) throws IOException, ClassNotFoundException {
        if (key >= size || key < 0) {
            throw new IOException();
        }
        for (int i = size - 1; i > key; --i) {
            stack.push((String) ois.readObject());
        }
        ois.readObject();
        oos.writeObject(data);
        while (!stack.isEmpty()) {
            oos.writeObject(stack.pop());
        }
    }

    @Override
    public void delete(Integer key) throws IOException, ClassNotFoundException {
        if (key >= size || key < 0) {
            throw new IOException();
        }
        for (int i = size - 1; i > key; --i) {
            stack.push((String) ois.readObject());
        }
        while (!stack.isEmpty()) {
            oos.writeObject(stack.pop());
        }
    }

}
