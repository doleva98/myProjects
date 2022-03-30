package il.co.ilrd.iosystem;

import java.io.IOException;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;

import il.co.ilrd.observer.Callback;

public class BackUpFileHandler {
    private Callback<String> callback = new Callback<>(str -> update(str),
            () -> {
            });
    private String originalFileName;
    private FileCRUD originalFileCrud = null;
    private FileCRUD backUpFileCrud = null;

    public BackUpFileHandler(String originalFile, String backUpFile) throws IOException {
        this.originalFileName = Paths.get(originalFile).getFileName().toString();
        originalFileCrud = new FileCRUD(originalFile, true);
        backUpFileCrud = new FileCRUD(backUpFile, true);
        backUpFileCrud.cleanFile();
        for (int i = 0; i < originalFileCrud.size(); ++i) {
            backUpFileCrud.create(originalFileCrud.read(i));
        }
    }

    public void update(String pathAndEntryState) {
        if (!pathAndEntryState.split(" ")[0].equals(originalFileName)) {
            return;
        }
        if (StandardWatchEventKinds.ENTRY_MODIFY.name().equals(pathAndEntryState.split(" ")[1])) {
            try {
                System.out.println("entry modified");

                if (originalFileCrud.size() > backUpFileCrud.size()) {
                    backUpFileCrud.create(originalFileCrud.read(originalFileCrud.size() - 1));
                } else if (originalFileCrud.size() < backUpFileCrud.size()) {
                    for (int i = 0; i < originalFileCrud.size(); ++i) {
                        if (!backUpFileCrud.read(i).equals(originalFileCrud.read(i))) {
                            backUpFileCrud.delete(i);
                            break;
                        }
                    }
                } else {
                    for (int i = 0; i < originalFileCrud.size(); ++i) {
                        if (!backUpFileCrud.read(i).equals(originalFileCrud.read(i))) {
                            backUpFileCrud.update(i, originalFileCrud.read(i));
                        }
                    }
                }
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        } else if (StandardWatchEventKinds.ENTRY_DELETE.name().equals(pathAndEntryState.split(" ")[1])) {
            System.out.println("entry deleted");
        } else if (StandardWatchEventKinds.ENTRY_CREATE.name().equals(pathAndEntryState.split(" ")[1])) {
            System.out.println("entry created");
        }
    }

    public void register(FolderMonitor subject) {
        subject.registerObserver(callback);
    }

    public void unregister(FolderMonitor subject) {
        subject.unregisterObserver(callback);
    }
}
