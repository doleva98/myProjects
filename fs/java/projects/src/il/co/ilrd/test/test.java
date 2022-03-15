package il.co.ilrd.test;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.TreeMap;
import java.util.concurrent.PriorityBlockingQueue;

class A {

    
    public static void main(String[] args) {
        Queue<Integer> q = new PriorityQueue<>();
        Queue<Integer> bq = new PriorityBlockingQueue<>(4);
        for (int i = 0; i < 1000; ++i) {
            bq.add(i);
        }

    }
}