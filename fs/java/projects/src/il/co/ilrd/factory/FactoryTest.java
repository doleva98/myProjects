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

}

class FactoryTest {
    public static void main(String[] args) {
        Factory<Animal, Integer, String> factory = new Factory<>();
        factory.add("Cat", (data) -> (new Cat()));
        Animal c1 = factory.create("Cat");
        c1.speak();

        System.out.println("***********");

        factory.add("Cat with height", (data) -> (new Cat(data)));
        Animal c2 = factory.create("Cat with height", 55);
        c2.speak();

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

        System.out.println("***********3***********");

        factory.add("Cat synthetic sugar", Cat::CreateWithHeight);
        Animal c5 = factory.create("Cat synthetic sugar");
        c5.speak();

        System.out.println("***********");

        factory.add("Cat synthetic sugar with height", Cat::CreateWithHeight);
        Animal c6 = factory.create("Cat synthetic sugar with height");
        c6.speak();

        System.out.println("***********4***********");

        factory.add("Cat synthetic sugar", new Cat()::CreateInstanceWithHeight);
        Animal c7 = factory.create("Cat synthetic sugar");
        c7.speak();

        System.out.println("***********");

        factory.add("Cat synthetic sugar with height", new Cat()::CreateInstanceWithHeight);
        Animal c8 = factory.create("Cat synthetic sugar with height");
        c8.speak();

        System.out.println("***********5***********");

        factory.add("Cat synthetic sugar", data::foo);
        Animal c9 = factory.create("Cat synthetic sugar");
        c9.speak();

        System.out.println("***********");

        factory.add("Cat synthetic sugar with height", data::foo);
        Animal c10 = factory.create("Cat synthetic sugar with height");
        c10.speak();

    }
}

class data {
    public static Animal foo(int a) {
        return new Cat().CreateInstanceWithHeight(a);
    }
}

class syntheticSugar {

    public static Animal applyStatic(Integer r) {
        return Cat.Create();
    }

}