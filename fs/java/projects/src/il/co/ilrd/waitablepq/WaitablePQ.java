package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

class WaitablePQ<T extends Comparable<? super T>> {
    private Queue<T> queue;

    public WaitablePQ(int initialCapacity) {
        queue = new PriorityQueue<>(initialCapacity);
    }

    public WaitablePQ() {
        queue = new PriorityQueue<>();
    }

    public WaitablePQ(Comparator<? super T> comp) {
        queue = new PriorityQueue<>(comp);
    }

    public WaitablePQ(int initialCapacity, Comparator<? super T> comp) {
        queue = new PriorityQueue<>(initialCapacity, comp);
    }

    synchronized public void enqueue(T element) {
    }

    synchronized public void dequeue() {
    }

    synchronized public void remove() {

    }

    synchronized public int size() {

    }

    synchronized public boolean isEmpty() {

    }
}
