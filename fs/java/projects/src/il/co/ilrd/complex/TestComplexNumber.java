
package il.co.ilrd.complex;


import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.Before;
import org.junit.Test;

public class TestComplexNumber {

    ComplexNumber c1;
    ComplexNumber c2;
    ComplexNumber c3;

    @Before
    public void before() {
        c1 = ComplexNumber.createFromReal(4);
        c1.setImg(0);
        c2 = ComplexNumber.createFromImg(4);
        c2.setReal(0);
        c3 = ComplexNumber.createFromReal(0);
        c1.setImg(0);

    }

    @Test
    public void testAdd() {
        c2 = ComplexNumber.add(c1, c2);
        c3.setImg(4);
        c3.setReal(4);
        assertEquals(c2, c3);
    }

    @Test
    public void testCompareTo() {
        assertTrue(c1.compareTo(c2) > 0);
        assertTrue(c2.compareTo(c3) == 0);
        assertTrue(c2.compareTo(c1) < 0);
        assertTrue(true);
    }

    @Test
    public void testEquals() {
        c1.setReal(0);
        assertEquals(c1, c3);
        assertTrue(c1.equals(c3));
        assertFalse(c1.equals(c2));
    }

    @Test
    public void testGetImg() {
        assertEquals(c1.getImg(), 0);
        assertEquals(c2.getImg(), 4);

    }

    @Test
    public void testGetReal() {
        assertEquals(c1.getReal(), 4);
        assertEquals(c2.getReal(), 0);

    }

    /*     @Test
    public void testHashCode() {
    
    } */

    @Test
    public void testIsImg() {
        assertTrue(c2.isImg());
        assertFalse(c1.isImg());
    }

    @Test
    public void testIsReal() {
        assertTrue(c2.isImg());
        assertFalse(c1.isImg());
    }

    @Test
    public void testParsing() {
        c3 = ComplexNumber.parsing("4 + 0 i");
        assertEquals(c1, c3);
        c3 = ComplexNumber.parsing("40 + 120 i");
        assertEquals(c3.toString(), "40.0+120.0i");
    }

    @Test
    public void testSubtract() {
        c2 = ComplexNumber.subtract(c1, c2);
        c3.setImg(-4);
        c3.setReal(4);
        assertEquals(c2, c3);
    }

    @Test
    public void testToString() {
        assertEquals(c1.toString(), "4.0+0.0i");
        assertEquals(c2.toString(), "0.0+4.0i");

    }

    public static void main(String[] args) {
        System.out.println(ComplexNumber.parsing("3.5 + 2 i"));

    }
}
