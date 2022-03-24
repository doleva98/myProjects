package il.co.java_quizzes.PizzaStore;

public interface Pizza {

    public abstract int getPrice();

    public abstract String getDescription();
}

class PeppyPaneer
        implements Pizza {
    private int price = 10;
    private String description = "Peppy Paneer";

    @Override
    public int getPrice() {
        return price;
    }

    @Override
    public String getDescription() {
        return description;
    }

}

class Margherita
        implements Pizza {
    private int price = 12;
    private String description = "Margherita";

    @Override
    public int getPrice() {
        return price;
    }

    @Override
    public String getDescription() {
        return description;
    }

}

class ChickenFiesta
        implements Pizza {
    private int price = 13;
    private String description = "Chicken Fiesta";

    @Override
    public int getPrice() {
        return price;
    }

    @Override
    public String getDescription() {
        return description;
    }

}

class Farmhouse
        implements Pizza {
    private int price = 11;
    private String description = "Farmhouse";

    @Override
    public int getPrice() {
        return price;
    }

    @Override
    public String getDescription() {
        return description;
    }

}