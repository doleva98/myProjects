package il.co.ilrd.test;


class Foo {

    public Foo() {
        System.out.println(toString());
    }

    public static void main(String[] args) {
        Foo f = new Foo();
    }

    @Override
    public String toString()
    {
        return "Heloo Dori";
    }
}