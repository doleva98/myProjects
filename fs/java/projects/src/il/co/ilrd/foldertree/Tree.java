package il.co.ilrd.foldertree;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Tree {
    private Folder rootFolder;

    public Tree(String name) {
        rootFolder = new Folder(new File(name));
    }

    public void print() {
        rootFolder.print(0);
    }

    private class Folder implements AbstractFile {
        private final File folder;
        private List<AbstractFile> listOfFiles;

        public Folder(File folder) {
            this.folder = folder;
            listOfFiles = new ArrayList<>();

            File[] fArray = this.folder.listFiles();
            Arrays.sort(fArray);/* File is comparable by path names */
            if (fArray == null) {
                return;
            }
            for (File f : fArray) {
                if (f.isDirectory()) {
                    listOfFiles.add(new Folder(f));
                } else {
                    listOfFiles.add(new LeafFile(f));
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
            System.out.println(file.getName());
        }
    }

    public static void main(String[] args) {
        Tree t = new Tree(".");
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