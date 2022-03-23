/* maor cr */
package il.co.ilrd.foldertree;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

import il.co.ilrd.utility.ColorsFont;

public class Tree {
    private Folder rootFolder;
    public int numFolders = 0;
    private int numFiles = 0;

    public Tree(String name) {
        Objects.requireNonNull(name);

        File f = new File(name);
        if (!f.exists() || !f.isDirectory()) {
            throw new IllegalArgumentException();
        }
        rootFolder = new Folder(f);
    }

    public void print() {
        rootFolder.print(0);
        System.out.println("directories " + numFolders + " files " + numFiles);
    }

    private class Folder implements AbstractFile {
        private final File folder;
        private List<AbstractFile> listOfFiles;

        public Folder(File folder) {
            ++numFolders;
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
            ++numFiles;
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
                System.out.print(ColorsFont.ANSI_RED);
                break;
            case 1:
                System.out.print(ColorsFont.ANSI_GREEN);
                break;
            case 2:
                System.out.print(ColorsFont.ANSI_RESET);
                break;
            case 3:
                System.out.print(ColorsFont.ANSI_BLUE);
                break;
            case 4:
                System.out.print(ColorsFont.ANSI_PURPLE);
                break;
            case 5:
                System.out.print(ColorsFont.ANSI_RED);
                break;
            case 6:
                System.out.print(ColorsFont.ANSI_CYAN);
                break;
            case 7:
                System.out.print(ColorsFont.ANSI_YELLOW);
                break;
        }
    }
}