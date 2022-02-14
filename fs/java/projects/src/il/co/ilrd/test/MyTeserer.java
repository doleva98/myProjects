import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;

import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

public class MyTeserer implements h{
    static int x;

    @Test
    public void testHigh() {
        assertFalse(false);
    }

    @Test
    public void testT() {
        assertEquals(MyTest.high(x, 1), x);
    }

    @BeforeClass
    public static void g() {
        x = 6;
    }
}

interface h {
    default void foo()
    {
        System.out.println("hi");
    }
}

interface g {
    default void foo()
    {
        System.out.println("wow");
    }
}