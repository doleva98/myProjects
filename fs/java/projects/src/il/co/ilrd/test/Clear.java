package il.co.ilrd.test;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

class Outer implements Serializable {
    private int i = 10, j = 33;
    transient int k = 30;
    transient static int k1 = 30;
    transient final int k2 = 30;

    public static void main(String[] args) {
        Outer o = new Outer();
        try (FileOutputStream fos = new FileOutputStream("hello.txt")) {
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(o);
            try (FileInputStream fis = new FileInputStream("hello.txt")) {
                ObjectInputStream oos2 = new ObjectInputStream(fis);

                Outer outer = (Outer) oos2.readObject();
                System.out.println("i = " + outer.i);
                System.out.println("j = " + outer.j);
                System.out.println("k = " + outer.k);
                System.out.println("k1 = " + outer.k1);
                System.out.println("k2 = " + outer.k2);

            } catch (ClassNotFoundException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
