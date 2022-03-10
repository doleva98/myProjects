package il.co.ilrd.factory;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class FactoryTree {
    private AbstractFile rootFolder;
    private Factory<AbstractFile, File, String> factory;
    public int numFolders = 0;
    private int numFiles = 0;

    public FactoryTree(String name) {
        Objects.requireNonNull(name);
        File f = new File(name);
        if (!f.exists() || !f.isDirectory()) {
            throw new IllegalArgumentException();
        }
        factory = new Factory<>();
        factory.add("folder", (str) -> new Folder(str));
        factory.add("file", (str) -> new LeafFile(str));

        rootFolder = factory.create("folder", f);
    }

    public void print() {
        rootFolder.print(0);
        System.out.println("directories " + numFolders + " files " + numFiles);
    }

    private class Folder implements AbstractFile {
        private final File folder;
        private List<AbstractFile> listOfFiles;

        public Folder(File folder) {

            this.folder = folder;
            listOfFiles = new ArrayList<>();

            File[] fArray = folder.listFiles();
            Arrays.sort(fArray);/* File is comparable by path names */

            for (File f : fArray) {
                if (f.isDirectory()) {
                    if (!f.isHidden()) {
                        ++numFolders;
                    }
                    listOfFiles.add(factory.create("folder", f));
                } else {
                    ++numFiles;
                    listOfFiles.add(factory.create("file", f));
                }
            }

        }

        @Override
        public void print(int offSet) {
            colorIt(offSet);
            for (int i = 0; i < offSet; ++i) {
                System.out.print("\t");
            }
            System.out.println(folder.getName());
            ++offSet;
            for (AbstractFile file : listOfFiles) {
                file.print(offSet);
            }
        }
    }

    interface AbstractFile {
        void print(int offSet);
    }

    private class LeafFile implements AbstractFile {
        private final File file;

        public LeafFile(File file) {
            this.file = file;
        }

        @Override
        public void print(int offSet) {
            colorIt(offSet);
            for (int i = 0; i < offSet; ++i) {
                System.out.print("\t");
            }
            System.out.println(file);
        }
    }

    public static void main(String[] args) {
        FactoryTree t = new FactoryTree(".");
        t.print();
    }

    private static void colorIt(int offSet) {
        switch (offSet) {
            case 0:
                System.out.print(Color.ANSI_RED);
                break;
            case 1:
                System.out.print(Color.ANSI_GREEN);
                break;
            case 2:
                System.out.print(Color.ANSI_RESET);
                break;
            case 3:
                System.out.print(Color.ANSI_BLUE);
                break;
            case 4:
                System.out.print(Color.ANSI_PURPLE);
                break;
            case 5:
                System.out.print(Color.ANSI_RED);
                break;
            case 6:
                System.out.print(Color.ANSI_CYAN);
                break;
            case 7:
                System.out.print(Color.ANSI_YELLOW);
                break;
        }
    }
}

class Color {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLACK = "\u001B[30m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_WHITE = "\u001B[37m";
}