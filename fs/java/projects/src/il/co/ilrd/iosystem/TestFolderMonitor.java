package il.co.ilrd.iosystem;

import java.io.IOException;
import java.util.Scanner;

public class TestFolderMonitor {
    public static void main(String[] args) throws IOException {
        FolderMonitor fm = new FolderMonitor(
                "C:\\Users\\dolev\\Desktop\\git\\dolev-arev\\fs\\java\\projects\\src\\il\\co\\ilrd\\iosystem\\dir");
        fm.start();
        BackUpFileHandler backUpFileHandler1 = new BackUpFileHandler(
                "C:\\Users\\dolev\\Desktop\\git\\dolev-arev\\fs\\java\\projects\\src\\il\\co\\ilrd\\iosystem\\dir\\hello1.txt",
                "C:\\Users\\dolev\\Desktop\\git\\dolev-arev\\fs\\java\\projects\\src\\il\\co\\ilrd\\iosystem\\dir\\bu1.txt");
        backUpFileHandler1.register(fm);
    }
}
