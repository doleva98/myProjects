/* shani */
package il.co.ilrd.vending_machine;

import java.util.List;
import java.util.ListIterator;

public class VendingMachine {
    private int money_in_machine;
    private List<Product> list_of_products;
    private Vmstate state;
    private PrintScreen output;
    private boolean isRunning;
    private Thread running_thread;
    private long startTime;

    public VendingMachine(List<Product> list, PrintScreen output) {
        money_in_machine = 0;
        list_of_products = list;
        state = Vmstate.OFF;
        this.output = output;
        isRunning = false;

        output.printToMachine("vending machine is ready for use");
    }

    public void turnOffMachine() {
        state.turnOffMachine(this);
    }

    public void turnOnMachine() {
        state.turnOnMachine(this);
    }

    public void payment(int amount) {
        state.payment(this, amount);
    }

    public void chooseProduct(String product) {
        state.chooseProduct(this, product);
    }

    public void cancel() {
        state.cancel(this);
    }

    private class ThreadWaitingOneSecond implements Runnable {
        private VendingMachine vm;

        public void run() {
            while (vm.isRunning) {
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    output.printToMachine("ERROR");
                }
                vm.state.checkTimeOut(vm);
            }
        }

        ThreadWaitingOneSecond(VendingMachine vm) {
            this.vm = vm;
        }
    }

    private enum Vmstate {
        OFF {
            @Override
            public void payment(VendingMachine vm, int amount) {
                vm.output.printToMachine("you cant pay when"
                        + " the machine is off");
            }

            @Override
            public void turnOffMachine(VendingMachine vm) {
                vm.output.printToMachine("the machine is already turned off");
            }

            @Override
            public void turnOnMachine(VendingMachine vm) {
                vm.output.printToMachine("turning machine on");
                vm.running_thread = new Thread(vm.new ThreadWaitingOneSecond(vm));
                vm.isRunning = true;
                vm.running_thread.start();
                vm.money_in_machine = 0;
                vm.state = Vmstate.WFP;
            }

            @Override
            public void chooseProduct(VendingMachine vm, String product) {
                vm.output.printToMachine("you cant choose a product when the machine is off");
            }

            @Override
            public void cancel(VendingMachine vm) {
                vm.output.printToMachine("cant cancel, the machine is turned off");
            }
        },
        WFP {/* waiting for payment */
            @Override
            public void payment(VendingMachine vm, int amount) {
                vm.state = Vmstate.WFS;
                vm.startTime = System.currentTimeMillis();
                super.payment(vm, amount);
            }

            @Override
            public void cancel(VendingMachine vm) {
                vm.output.printToMachine("cant cancel, you didnt insert money");
            }

            @Override
            public void chooseProduct(VendingMachine vm, String product) {
                vm.output.printToMachine("you cant choose product before inserting money");
            }
        },
        WFS {/* waiting for selection */

            @Override
            public void checkTimeOut(VendingMachine vm) {
                long currTime = System.currentTimeMillis();
                if (1000 < currTime - vm.startTime) {
                    cancel(vm);
                }
            }

            @Override
            public void chooseProduct(VendingMachine vm, String product) {
                vm.startTime = System.currentTimeMillis();
                ListIterator<Product> iter = vm.list_of_products.listIterator();
                while (iter.hasNext()) {
                    Product current_product = iter.next();
                    if (current_product.getName().equals(product)) {
                        if (current_product.getPrice() > vm.money_in_machine) {
                            vm.output.printToMachine("not enough money in machine, you need to add "
                                    + (current_product.getPrice() - vm.money_in_machine) + " dollars for "
                                    + current_product.getName()
                                    + "\nor you can choose another product");
                            return;
                        } else {
                            vm.money_in_machine -= current_product.getPrice();
                            vm.output.printToMachine("giving you " + current_product.getName() +
                                    "\nthere is " + vm.money_in_machine + " dollars left in the machine");
                            return;
                        }
                    }
                }
                vm.output.printToMachine("there is no such product");
            }
        };

        public void payment(VendingMachine vm, int amount) {
            vm.startTime = System.currentTimeMillis();
            vm.money_in_machine += amount;
            vm.output.printToMachine("vending machine got " + amount + " dollars");
            vm.output.printToMachine("vending machine has " + vm.money_in_machine + " dollars");
        }

        abstract public void chooseProduct(VendingMachine vm, String product);

        public void checkTimeOut(VendingMachine vm) {
        }

        public void cancel(VendingMachine vm) {
            vm.state = Vmstate.WFP;
            vm.money_in_machine = 0;
            vm.output.printToMachine("canceled, now has 0 dollars");
        }

        public void turnOffMachine(VendingMachine vm) {
            vm.output.printToMachine("turning machine off");
            vm.state = Vmstate.OFF;
            vm.isRunning = false;
            try {
                vm.running_thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        public void turnOnMachine(VendingMachine vm) {
            vm.output.printToMachine("the machine is already turned on");
        }
    }
}
