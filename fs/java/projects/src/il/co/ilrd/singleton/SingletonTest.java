package il.co.ilrd.singleton;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.Test;

public class SingletonTest {

    @Test
    public void t1() {
        SingletonLazyNotThreadSafe s1 = SingletonLazyNotThreadSafe.getInstance();
        SingletonLazyNotThreadSafe s2 = SingletonLazyNotThreadSafe.getInstance();
        assertEquals(s1, s2);
        assertTrue(s1 == s2);
    }

    @Test
    public void t2() {
        SingletonLazyThreadSafe s1 = SingletonLazyThreadSafe.getInstance();
        SingletonLazyThreadSafe s2 = SingletonLazyThreadSafe.getInstance();
        assertEquals(s1, s2);
        assertTrue(s1 == s2);
    }

    @Test
    public void t3() {
        SingletonDoubleLocking s1 = SingletonDoubleLocking.getInstance();
        SingletonDoubleLocking s2 = SingletonDoubleLocking.getInstance();
        assertEquals(s1, s2);
        assertTrue(s1 == s2);
    }

    @Test
    public void t4() {
        assertEquals(SingletonEnum.INSTANCE, SingletonEnum.INSTANCE);
        /* assertTrue(SingletonEnum.INSTANCE == SingletonEnum.INSTANCE); */
        assertEquals(SingletonEnum.doSomething(), SingletonEnum.INSTANCE.hashCode());
    }

    @Test
    public void t5() {
        SingletonThreadSafeEager s1 = SingletonThreadSafeEager.getInstance();
        SingletonThreadSafeEager s2 = SingletonThreadSafeEager.getInstance();
        assertEquals(s1, s2);
        assertTrue(s1 == s2);
    }

    @Test
    public void t6() {
        SingletonWithHelper s1 = SingletonWithHelper.getInstance();
        SingletonWithHelper s2 = SingletonWithHelper.getInstance();
        assertEquals(s1, s2);
        assertTrue(s1 == s2);
    }
}
