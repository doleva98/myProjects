package il.co.ilrd.iosystem;

public class FileCRUDTest {
    public static void main(String[] args) {
        try (FileCRUD fcrud = new FileCRUD("a.txt")) {
            fcrud.create("HELLO WORLD");
            fcrud.create("WOWWWW");
            fcrud.create("HOOO YAYYY");
            fcrud.create("DOLEVVDSS");
            System.out.println("round 1");

            for (int i = 0; i < 4; ++i) {
                System.out.println(fcrud.read(i));
            }
            // fcrud.update(1, "DOLEV");
            // System.out.println(fcrud.read(1));

            /*System.out.println("round 2");
            
            for (int i = 0; i < 3; ++i) {
                System.out.println(fcrud.read(i));
            }
            System.out.println("round 3");
            
            fcrud.delete(0);
            for (int i = 0; i < 2; ++i) {
                System.out.println(fcrud.read(i));
            } */
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
