package vending_machine;

import java.util.List;
import java.util.ListIterator;

public class VendingMachine {
    private int money_in_machine;
    private List<Product> list_of_products;
    private Vmstate state;
    PrintScreen output;

    public VendingMachine(List<Product> list, PrintScreen output) {

        money_in_machine = 0;
        list_of_products = list;
        state = Vmstate.WFP;
        this.output = output;

        output.printToMachine("vending machine is ready for use");
    }

    public void payment(int amount) {
        money_in_machine += amount;
        state.payment(this);
        output.printToMachine("vending machine got " + amount + " dollars");
        output.printToMachine("vending machine has " + money_in_machine + " dollars");
    }

    public void chooseProduct(String product) {
        state.chooseProduct(this, product);
    }

    public void cancel() {
        state.cancel(this);
    }

    private enum Vmstate {
        WFP {/* waiting for payment */
            @Override
            public void payment(VendingMachine vm) {
                vm.state = Vmstate.WFS;
            }

            @Override
            public void cancel(VendingMachine vm) {
                System.out.println("cant cancel, you didnt insert money");
            }

            @Override
            public void chooseProduct(VendingMachine vm, String product) {
                System.out.println("you cant choose product before inserting money");
            }
        },
        WFS {/* waiting for selection */
            @Override
            public void payment(VendingMachine vm) {
            }

            @Override
            public void chooseProduct(VendingMachine vm, String product) {
                ListIterator<Product> iter = vm.list_of_products.listIterator();
                while (iter.hasNext()) {
                    Product current_product = iter.next();
                    if (current_product.getName().equals(product)) {
                        if (current_product.getPrice() > vm.money_in_machine) {
                            System.out.println("not enough money in machine, you need to add "
                                    + (current_product.getPrice() - vm.money_in_machine) + " dollars for "
                                    + current_product.getName()
                                    + "\nor you can choose another product");
                        } else {
                            vm.money_in_machine -= current_product.getPrice();
                            System.out.println("giving you " + current_product.getName() +
                                    "\nthere is " + vm.money_in_machine + " dollars left in the machine");
                        }
                    }
                }
                System.out.println("there is no such product");
            }
        };

        abstract public void payment(VendingMachine vm);

        abstract public void chooseProduct(VendingMachine vm, String product);

        public void cancel(VendingMachine vm) {
            vm.state = Vmstate.WFP;
            vm.money_in_machine = 0;
            System.out.println("canceled, now has 0 dollars");
        }
    }
}
