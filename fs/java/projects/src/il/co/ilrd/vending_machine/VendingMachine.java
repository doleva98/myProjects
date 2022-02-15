package vending_machine;

import java.util.List;

public class VendingMachine {
    private int money_in_machine;
    List<Product> list_of_products;
    Vmstate state;

    public VendingMachine(List<Product> list) {
        money_in_machine = 0;
        list_of_products = list;
        /*  state =  */
    }

    public void payment(int amount) {
    }

    public void chooseProduct(Product product) {
    }

    public void cancel() {
    }

    private class Product implements ProductInterface {
        private int price;
        private String name;

        private Product(int price, String name) {
            this.price = price;
            this.name = name;
        }

        public int getPrice() {
            return price;
        }

        public String getName() {
            return name;
        }

    }

}
