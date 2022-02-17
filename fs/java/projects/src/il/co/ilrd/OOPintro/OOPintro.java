package il.co.ilrd.OOPintro;

class Vehicle {
    static String color;
    static {
        System.out.println("4");
    }
    {
        System.out.println("3");
    }

    Vehicle() {
        System.out.println("v con");

    }

    {
        System.out.println("2");
    }
}

class Car extends Vehicle {
    static int plate_id;
    {
        System.out.println("1");
    }
    static {
        System.out.println("5");
    }

    Car() {
        System.out.println("car con");
    }
}

class hello {
    public static void main(String[] args) {
        Car c = new Car();
        System.out.println(c);
    }

    static {
        System.out.println("10");
    }
}