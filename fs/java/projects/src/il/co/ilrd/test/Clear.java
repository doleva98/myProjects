package il.co.ilrd.test;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

class BaseInit {
    private int member1 = 1;
    private int member2 = 2;

    public BaseInit() {
        System.out.println("Base Ctor");
        printFirst();
        printSecond();
    }

    void printFirst() {
        System.out.println(member1);
    }

    private void printSecond() {
        System.out.println(member2);
    }
}

class DerivedInit extends BaseInit {
    private int member3 = 3;
    private int member4 = 4;

    public DerivedInit() {
        System.out.println("Derived Ctor");
        printFirst();
        printSecond();
    }

    void printFirst() {
        System.out.println(member3);
    }

    private void printSecond() {
        System.out.println(member4);
    }
}

class TestInit {
    public static void main(String[] args) {
        DerivedInit d = new DerivedInit();
    }
}

class check {
    private static final String InputFileName = null;
    private static final String OutputFileName = null;

    public static void main(String[] args) {

    }

    public void foo() throws IOException {
        int count = 0;
        if (System.in.read() != -1)
            count++;
        System.out.println("input has" + count + "chars.");
    }

    public void foo2() {
        InputStream in = null;
        OutputStream out = null;
        try {
            in = new FileInputStream("dfdf");
            out = new FileOutputStream("OutputFileName");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            try {
                out.close();
                in.close();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }
}