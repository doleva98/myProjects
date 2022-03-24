package il.co.java_quizzes.PizzaStore;

public abstract class PizzaDecorator implements Pizza {
    protected Pizza pizza;

    public PizzaDecorator(Pizza pizza) {
        this.pizza = pizza;
    }

}

class AddCapsicum extends PizzaDecorator {
    private final static int value = 3;

    public AddCapsicum(Pizza pizza) {
        super(pizza);
    }

    @Override
    public String getDescription() {
        return pizza.getDescription() + " with Capsicum";
    }

    @Override
    public int getPrice() {
        return value + pizza.getPrice();
    }

}

class AddBBQ extends PizzaDecorator {
    private final static int value = 5;

    public AddBBQ(Pizza pizza) {
        super(pizza);
    }

    @Override
    public String getDescription() {
        return pizza.getDescription() + " with BBQ";
    }

    @Override
    public int getPrice() {
        return value + pizza.getPrice();
    }

}

class AddJalapeno extends PizzaDecorator {
    private final static int value = 4;

    public AddJalapeno(Pizza pizza) {
        super(pizza);
    }

    @Override
    public String getDescription() {
        return pizza.getDescription() + " with Jalapeno";
    }

    @Override
    public int getPrice() {
        return value + pizza.getPrice();
    }

}

class AddPaneer extends PizzaDecorator {
    private final static int value = 2;

    public AddPaneer(Pizza pizza) {
        super(pizza);
    }

    @Override
    public String getDescription() {
        return pizza.getDescription() + " with Paneer";
    }

    @Override
    public int getPrice() {
        return value + pizza.getPrice();
    }

}

class AddFreshTomato extends PizzaDecorator {
    private final static int value = 1;

    public AddFreshTomato(Pizza pizza) {
        super(pizza);
    }

    @Override
    public String getDescription() {
        return pizza.getDescription() + "with Fresh Tomato";
    }

    @Override
    public int getPrice() {
        return value + pizza.getPrice();
    }

}