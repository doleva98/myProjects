package vending_machine;

import java.util.List;

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
            public void chooseProduct(VendingMachine vm, String product) {
            }

            @Override
            public void cancel(VendingMachine vm) {
            }
        },
        WFS {/* waiting for selection */
            @Override
            public void payment(VendingMachine vm) {
            }

            @Override
            public void chooseProduct(VendingMachine vm, String product) {
            }

            @Override
            public void cancel(VendingMachine vm) {
            }
        };

        abstract public void payment(VendingMachine vm);

        public void chooseProduct(VendingMachine vm, String product) {
        }

        public void cancel(VendingMachine vm) {
        }
    }
}
