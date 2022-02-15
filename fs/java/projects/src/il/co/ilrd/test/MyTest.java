/* 
class Outer {
    int x = 6;

    private void foo() {
        System.out.println("hello i am outer");
    }

    static class Inner {
        public void goo() {
            System.out.println("hello i am inner " + x);
            foo();
        }
    } 
} */

interface Person {
    void name();
}

class Main
{
    public static void main(String[] args) {
        Person p = new Person() {
            @Override
            public void name() {
                System.out.println("i am dolev");
            }
        };
        p.name();
    }
}