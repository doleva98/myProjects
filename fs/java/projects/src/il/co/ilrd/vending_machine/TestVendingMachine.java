package il.co.ilrd.vending_machine;

import java.util.ArrayList;
import java.util.List;

public class TestVendingMachine {

    public static void main(String[] args) {

        List<Product> list = new ArrayList<Product>();

        list.add(new ProductBottles(10, "Coca Cola"));
        list.add(new ProductBottles(5, "Sprite"));
        list.add(new ProductBottles(7, "Pepsi"));

        PrintScreen oc = new OutputClass();

        VendingMachine vm = new VendingMachine(list, oc);
        vm.cancel();
        vm.turnOnMachine();
        vm.chooseProduct("Sprite");
        vm.payment(1);
        vm.payment(1);

        try {
            Thread.sleep(400);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        vm.payment(4);
        vm.payment(7);
        vm.chooseProduct("Coca Cola");
        vm.chooseProduct("Sprite");
        vm.cancel();
        vm.chooseProduct("Pepsi");
        vm.chooseProduct("water");
        vm.payment(7);
        vm.chooseProduct("water");
        vm.turnOffMachine();
        vm.payment(4);

        vm.turnOnMachine();
        vm.payment(4);

        VendingMachine vm2 = new VendingMachine(list, oc);
        vm2.turnOnMachine();

        vm2.payment(4);
        vm2.turnOffMachine();
        vm.turnOffMachine();
    }
}

class OutputClass implements PrintScreen {
    public void printToMachine(String str) {
        System.out.println(str);
    }
}

class ProductBottles implements Product {
    private int price;
    private String name;

    public ProductBottles(int price, String name) {
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