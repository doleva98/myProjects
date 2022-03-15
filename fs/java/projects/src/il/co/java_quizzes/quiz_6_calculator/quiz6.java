package il.co.java_quizzes.quiz_6_calculator;

import java.util.HashMap;

class Test extends Thread {
    public static Object cacheLock = new Object();

    public static void main(String[] args) {
        Calculator calc = new Calculator();
        System.out.println(calc.operate("Addition", 4, 50));

        System.out.println(calc.operate("Subtraction", 4, 50));
        System.out.println(calc.operate("Multiplication", 4, 5));
        System.out.println(calc.operate("Division", 40, 5));

    }
}

class Calculator {
    HashMap<String, Operator> mapOperator = new HashMap<>();

    public Calculator() {
        addOperator("Addition", (a, b) -> a + b);
        addOperator("Subtraction", new Operator() {
            @Override
            public int operate(int a, int b) {
                return a - b;
            }
        });
        class Mul implements Operator {

            @Override
            public int operate(int a, int b) {
                return a * b;
            }

        }
        addOperator("Multiplication", new Mul());
        Operator div = new Operator() {

            @Override
            public int operate(int a, int b) {
                return a / b;
            }

        };
        addOperator("Division", div);

    }

    interface Operator {
        int operate(int a, int b);
    }

    public void addOperator(String key, Operator o) {
        mapOperator.put(key, o);
    }

    public int operate(String key, int a, int b) {
        return mapOperator.get(key).operate(a, b);
    }
}
