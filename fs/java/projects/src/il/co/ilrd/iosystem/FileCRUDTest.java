package il.co.ilrd.iosystem;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

public class FileCRUDTest {

    @Test
    public void test() {
        try (FileCRUD fcrud = new FileCRUD("/mnt/c/Users/dolev/Desktop/git/dolev-arev/fs/java/projects/a.txt")) {
            final int SIZE = 10;
            for (int i = 0; i < SIZE; ++i) {
                assertEquals(fcrud.create("wow"), i);
            }

            for (int i = 0; i < SIZE; ++i) {
                assertEquals(fcrud.read(i), "wow");
            }
            for (int i = 0; i < SIZE / 2; ++i) {
                fcrud.delete(i);
            }

            for (int i = 0; i < SIZE / 2; ++i) {
                assertEquals(fcrud.read(i), "wow");
            }
            for (int i = 0; i < SIZE / 2; ++i) {
                fcrud.update(i, "hello world");
            }

            for (int i = 0; i < SIZE / 2; ++i) {
                assertEquals(fcrud.read(i), "hello world");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

    }

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

            System.out.println("*********");

            fcrud.delete(0);

            for (int i = 0; i < 3; ++i) {
                System.out.println(fcrud.read(i));
            }
            System.out.println("*********");

            fcrud.update(0, "HEloow wrodl");
            for (int i = 0; i < 3; ++i) {
                System.out.println(fcrud.read(i));
            }

            System.out.println("*********");

            fcrud.update(1, "mot");

            for (int i = 0; i < 3; ++i) {
                System.out.println(fcrud.read(i));
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
