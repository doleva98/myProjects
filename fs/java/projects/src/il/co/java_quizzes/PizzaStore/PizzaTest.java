package il.co.java_quizzes.PizzaStore;

public class PizzaTest {
    public static void main(String[] args) {
        Pizza pizza = new PeppyPaneer();
        System.out.println("the price of " + pizza.getDescription() + " is " + pizza.getPrice());
        pizza = new AddCapsicum(pizza);
        System.out.println("the price of " + pizza.getDescription() + " is " + pizza.getPrice());
        pizza = new AddCapsicum(pizza);
        System.out.println("the price of " + pizza.getDescription() + " is " + pizza.getPrice());

        System.out.println("*************************");

        Pizza pizza2 = new Margherita();
        System.out.println("the price of " + pizza2.getDescription() + " is " + pizza2.getPrice());
        pizza2 = new AddFreshTomato(pizza2);
        System.out.println("the price of " + pizza2.getDescription() + " is " + pizza2.getPrice());
        pizza2 = new AddBBQ(pizza2);
        System.out.println("the price of " + pizza2.getDescription() + " is " + pizza2.getPrice());
        
    }
}
