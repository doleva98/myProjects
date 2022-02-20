package il.co.ilrd.reflection;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;

public class ObjectAnalyzer {
    public static void main(String[] args) {
        Class<Foo> my_class = Foo.class;
        System.out.println("******************************");
        System.out.println(my_class.getSuperclass().getName());

        System.out.println("******************************");

        for (Field i : my_class.getFields()) {
            System.out.println(i.getModifiers());
        }

        System.out.println("******************************");

        for (Class<?> i : my_class.getInterfaces()) {
            System.out.println(i.getName());
        }

        System.out.println("******************************");
        Foo f = new Foo();
        /*  try {
            f = my_class.newInstance();
        } catch (InstantiationException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } */
        Object o[] = new Object[0];
        try {
            my_class.getMethods()[0].invoke(f, o);
        } catch (IllegalAccessException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (SecurityException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}

class Foo implements i {
    public int x;
    String s;
    public void f1() {
        System.out.println("hello i am FVCFOO");
    }

    public Foo() {
        
        s = "grrg";
        this.x = 2;
    }
}

interface i {
    void f1();
}

class h {
    
}