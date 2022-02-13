import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.Before;
import org.junit.Test;

public class MyTeserer {
    static int x;
    @Test
    public void testHigh() {

    }

    @Test
    public void testT() {
        assertEquals(MyTest.high(x, 1), x);
    }

    @Before
    public static void g()
    {
        x = 6;
    }
}
