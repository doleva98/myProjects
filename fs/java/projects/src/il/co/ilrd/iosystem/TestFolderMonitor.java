package il.co.ilrd.iosystem;

import java.io.IOException;

public class TestFolderMonitor {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        FolderMonitor fm = new FolderMonitor(
                "C:\\Users\\dolev\\Desktop\\git\\dolev-arev\\fs\\java\\projects\\src\\il\\co\\ilrd\\iosystem\\dir");
        String originalFile = "C:\\Users\\dolev\\Desktop\\git\\dolev-arev\\fs\\java\\projects\\src\\il\\co\\ilrd\\iosystem\\dir\\hello1.txt";
        String backUpFile = "C:\\Users\\dolev\\Desktop\\git\\dolev-arev\\fs\\java\\projects\\src\\il\\co\\ilrd\\iosystem\\dir\\bu1.txt";
        BackUpFileHandler backUpFileHandler1;

        backUpFileHandler1 = new BackUpFileHandler(originalFile,
                backUpFile);

        backUpFileHandler1.register(fm);
        fm.start();

    }
}
