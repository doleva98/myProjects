/* Yoni */
package il.co.ilrd.factory;

import java.util.function.Function;

interface Animal {
    void speak();
}

class Cat implements Animal {
    private int height = 1;

    public Cat() {
    }

    public Cat(int height) {
        this.height = height;
    }

    public int getHeight() {
        return this.height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    @Override
    public void speak() {
        System.out.println("MEOW my height is " + height);
    }

    public static Cat Create() {
        return new Cat();
    }

    public static Cat CreateWithHeight(int height) {
        return new Cat(height);
    }

    public Cat CreateInstance() {
        return new Cat();
    }

    public Cat CreateInstanceWithHeight(int height) {
        return new Cat(height);
    }

    public Cat CreateInstance(Data d) {
        return new Cat();
    }

}

class FactoryTest {
    public static void main(String[] args) {

        /* lambda */

        Factory<Animal, Integer, String> factory = new Factory<>();
        factory.add("Cat", (data) -> (new Cat()));
        Animal c1 = factory.create("Cat");
        c1.speak();

        System.out.println("***********");

        factory.add("Cat with height", (data) -> (new Cat(data)));
        Animal c2 = factory.create("Cat with height", 55);
        c2.speak();

        /* anonymous class */

        System.out.println("***********2***********");

        factory.add("Cat anonymous", new Function<Integer, Animal>() {

            @Override
            public Animal apply(Integer t) {
                return new Cat();
            }

        });
        Animal c3 = factory.create("Cat anonymous");
        c3.speak();

        System.out.println("***********");

        factory.add("Cat anonymous with height", new Function<Integer, Animal>() {

            @Override
            public Animal apply(Integer t) {
                return new Cat(t);
            }

        });

        Animal c4 = factory.create("Cat anonymous with height", 100);
        c4.speak();

        /* static method */
        System.out.println("******3*****");

        factory.add("Cat syntactic sugar sugar with height", Cat::CreateWithHeight);
        Animal c6 = factory.create("Cat syntactic sugar sugar with height", 5000);
        c6.speak();

        /* instance method */
        System.out.println("***********4***********");

        factory.add("Cat syntactic sugar sugar with height", new Cat()::CreateInstanceWithHeight);
        Animal c8 = factory.create("Cat syntactic sugar sugar with height", 600);
        c8.speak();

        /* sugar method */

        System.out.println("***********5***********");
        Factory<Animal, Data, String> factory2 = new Factory<>();

        factory2.add("Cat syntactic sugar sugar", Data::foo);
        Data d = new Data(485);
        Animal c9 = factory2.create("Cat syntactic sugar sugar", d);
        c9.speak();

    }

}

class Data {
    private int d;

    public Data(int d) {
        this.d = d;
    }

    public Animal foo() {
        return new Cat(d);
    }
}