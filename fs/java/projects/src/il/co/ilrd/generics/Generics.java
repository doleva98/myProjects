package il.co.ilrd.generics;

import java.util.ArrayList;
import java.util.List;

public class Generics {
    public static void main(String[] args) {

        List<String> v = new ArrayList<>();
        v.add("test");
        String i = (String) v.get(0);

        System.out.println(i);

        Integer[] a = new Integer[] { 1, 4, 65, 7 };
        Double[] b = new Double[4];
        b[0] = (double) 3;
        b[1] = (double) 7;
        b[2] = (double) 65;
        b[3] = (double) 4;

        Float[] c = new Float[] { (float) 1.4, (float) 4, (float) 65.4, (float) 7 };

        printArray(a);
        printArray(b);
        printArray(c);

        FooRefernce<Integer[]> r1 = new FooRefernce<>(a);
        FooRefernce<Double[]> r2 = new FooRefernce<>(b);
        FooRefernce<Float[]> r3 = new FooRefernce<>(c);

        printArray(r1.getRefernece());

        System.out.println(r1.getClass().getName());
        System.out.println(r2.getClass().getName());
        System.out.println(r3.getClass().getName());

        List<Object> l = new ArrayList<>();
        /*  l.add("testy"); */
        printHello(l);

        /* @SuppressWarnings("rawtypes") */
        /*List rawList;
        List<?> listOfAnyType;
        List<Object> l1 = new ArrayList<Object>();
        List<String> l2 = new ArrayList<String>();
        List<Integer> l3 = new ArrayList<Integer>();
        List<? extends String> l4 = new ArrayList<>();
        
        rawList = listOfAnyType;
        
        rawList = l2;
        rawList = l3;
        listOfAnyType = l2;
        listOfAnyType = l3;
        listOfAnyType = l1;
        l2 = rawList;
        l1 = (List) l2;
        l4 = l2;*/
    }

    public static <T extends Number> void printArray(T[] a) {
        for (T item : a) {
            System.out.println(item);
        }
        System.out.println();

    }

    public static void printHello(List<Object> a) {
        for (Object item : a) {
            System.out.println(item);
        }
        System.out.println();
    }

    /*  public static <T> T foo() {
        return new T();
    } */

}

class FooRefernce<T extends Object> {
    private T refernece;

    public FooRefernce(T refernece) {
        this.refernece = refernece;
    }

    public T getRefernece() {
        return refernece;
    }

    public void setRefernece(T refernece) {
        this.refernece = refernece;
    }

}