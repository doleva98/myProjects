package il.co.ilrd.foldertree;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class Tree {
    private final String currFileName;
    private List<AbstractFile> listOfFiles = new ArrayList<>();

    public Tree(String name) {
        currFileName = name;
        File currentFile = new File(name);
        File[] fArray = currentFile.listFiles();
        for (File f : fArray) {
            if (f.isDirectory()) {
                listOfFiles.add(new Folder(f.getName()));
            } else {
                listOfFiles.add(new LeafFile(f.getName()));
            }
        }
    }

    public void print() {
        System.out.println(currFileName);
        for (AbstractFile file : listOfFiles) {
            file.print();
        }
    }

    private class Folder implements AbstractFile {
        private final String folderName;
        private List<AbstractFile> listOfFiles;

        public Folder(String folderName) {
            this.folderName = folderName;
            listOfFiles = new ArrayList<>();

            File currentFile = new File(folderName);
            File[] fArray = currentFile.listFiles();
            if (fArray == null) {
                return;
            }
            for (File f : fArray) {
                if (f.isDirectory()) {
                    listOfFiles.add(new Folder(f.getName()));
                } else {
                    listOfFiles.add(new LeafFile(f.getName()));
                }
            }

        }

        @Override
        public void print() {
            System.out.println(folderName);
            for (AbstractFile file : listOfFiles) {
                file.print();
            }
        }
    }

    private class LeafFile implements AbstractFile {
        private final String fileName;

        public LeafFile(String fileName) {
            this.fileName = fileName;
        }

        @Override
        public void print() {
            System.out.println(fileName);
        }

    }

    public static void main(String[] args) {
        Tree t = new Tree(".");
        t.print();
    }

}

interface AbstractFile {
    void print();
}