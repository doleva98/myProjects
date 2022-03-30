package il.co.ilrd.iosystem;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

class Mama implements Serializable {
    String s;
}

public class CheckSerial implements Serializable {
    public Mama o;

    public CheckSerial() {
    }

    public static void main(String[] args) {
        CheckSerial c1 = new CheckSerial();
        c1.o = new Mama();
        c1.o.s = "hello world";
        CheckSerial c2 = new CheckSerial();
        c2.o = c1.o;

        System.out.println(c1.o.s);
        c2.o.s = "wow";
        System.out.println(c1.o.s);

        System.out.println("BEFORE");
        String str = "HELLO WORLD";
        try (FileOutputStream fos = new FileOutputStream("a.txt")) {
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(c1);
            oos.writeObject(c2);
            oos.writeObject(str);
        } catch (IOException e) {
            e.printStackTrace();
        }
        CheckSerial s1;
        CheckSerial s2;

        try (FileInputStream fos = new FileInputStream("a.txt")) {
            ObjectInputStream oos = new ObjectInputStream(fos);
            s1 = (CheckSerial) oos.readObject();
            s2 = (CheckSerial) oos.readObject();
            System.out.println((String) oos.readObject());
            System.out.println(s1.o.s);
            s2.o.s = "BEFORE";

            System.out.println(s1.o.s);

        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }

    }
}
