package il.co.ilrd.stackimp;

import java.util.ArrayList;
import java.util.List;

public class StackImp<T> {
    List<T> elements = new ArrayList<>();

    public void push(T element) {
        elements.add(element);
    }

    public T pop() {
        return elements.remove(elements.size() - 1);
    }

    public T peek() {
        return elements.get(elements.size() - 1);
    }

    public void merge(StackImp<T> other) {
        elements.addAll(other.elements);
    }

    public boolean isEmpty() {
        return elements.isEmpty();
    }

    public int size() {
        return elements.size();
    }

    public void clear() {
        elements.clear();
    }

    public void print() {
        System.out.println(elements);
    }

    public void print(String message) {
        System.out.println(message + elements);
    }

    

}
