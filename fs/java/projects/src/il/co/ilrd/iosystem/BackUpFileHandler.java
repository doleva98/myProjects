package il.co.ilrd.iosystem;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;
import java.util.List;

import il.co.ilrd.observer.Callback;

public class BackUpFileHandler {
    private Callback<String> callback = new Callback<>(str -> {
        try {
            update(str);
        } catch (IOException e) {
            e.printStackTrace();
        }
    },
            () -> {
            });
    private Path originalFilePath;
    private FileCRUD backUpFileCrud = null;
    private List<String> lines;

    public BackUpFileHandler(String originalFile, String backUpFile) throws IOException, ClassNotFoundException {
        originalFilePath = Paths.get(originalFile);
        backUpFileCrud = new FileCRUD(backUpFile, true);
        lines = Files.readAllLines(originalFilePath);
        for (int i = 0; i < lines.size(); ++i) {
            backUpFileCrud.create(lines.get(i));
        }
    }

    public void update(String pathAndEntryState) throws IOException {
        if (!pathAndEntryState.split(" ")[0].equals(originalFilePath.getFileName().toString())) {
            return;
        }
        lines = Files.readAllLines(originalFilePath);
        System.out.println(lines);
        if (StandardWatchEventKinds.ENTRY_MODIFY.name().equals(pathAndEntryState.split(" ")[1])) {
            try {
                System.out.println(lines.size());
                System.out.println(backUpFileCrud.size());
                if (lines.size() > backUpFileCrud.size()) {

                    for (int i = 0; i < backUpFileCrud.size(); ++i) {
                        if (!backUpFileCrud.read(i).equals(lines.get(i))) {
                            backUpFileCrud.update(i, lines.get(i));
                        }
                    }
                    for (int i = backUpFileCrud.size(); i < lines.size(); ++i) {
                        backUpFileCrud.create(lines.get(i));
                    }

                } else if (lines.size() < backUpFileCrud.size()) {
                    for (int i = 0; i < lines.size(); ++i) {
                        if (!backUpFileCrud.read(i).equals(lines.get(i))) {
                            backUpFileCrud.delete(i);
                            --i;
                            break;
                        }
                    }
                    for (int i = lines.size(); i < backUpFileCrud.size(); ++i) {
                        backUpFileCrud.delete(i);
                    }
                } else {

                    for (int i = 0; i < lines.size(); ++i) {
                        if (!backUpFileCrud.read(i).equals(lines.get(i))) {
                            backUpFileCrud.update(i, lines.get(i));
                        }
                    }
                }
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        } else if (StandardWatchEventKinds.ENTRY_DELETE.name().equals(pathAndEntryState.split(" ")[1])) {
        } else if (StandardWatchEventKinds.ENTRY_CREATE.name().equals(pathAndEntryState.split(" ")[1])) {
        }
    }

    public void register(FolderMonitor subject) {
        subject.registerObserver(callback);
    }

    public void unregister(FolderMonitor subject) {
        subject.unregisterObserver(callback);
    }
}
