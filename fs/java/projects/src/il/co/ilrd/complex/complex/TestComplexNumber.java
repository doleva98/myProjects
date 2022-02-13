package complex;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.BeforeClass;
import org.junit.Test;

public class TestComplexNumber {
    Complex c1;
    Complex c2;
    Complex c3;

    @BeforeClass
    public void first() {
        c1 = new Complex(0, 0);
        c2 = new Complex(0, 0);
        c3 = new Complex(5, 9);

    }

    @Test
    public void testCompareTo() {

    }

    @Test
    public void testEquals() {
        assertTrue(c1.equals(c2));
        assertFalse(c1.equals(c3));
    }

    @Test
    public void testGetImg() {

    }

    @Test
    public void testGetReal() {

    }

    @Test
    public void testHashCode() {

    }

    @Test
    public void testIsImg() {

    }

    @Test
    public void testIsReal() {

    }

    @Test
    public void testParsing() {

    }

    @Test
    public void testSetImg() {

    }

    @Test
    public void testSetReal() {

    }

    @Test
    public void testToString() {

    }
}
