package il.co.ilrd.test;

class Test {
    public static void main(String[] args) {
        try {
            Thread t = new Thread(new Runnable() {

                @Override
                public void run() {
                    throw new RuntimeException();
                }

            });
            t.start();
        } catch (Exception e) {
            System.out.println("************");
        }
    }
}
