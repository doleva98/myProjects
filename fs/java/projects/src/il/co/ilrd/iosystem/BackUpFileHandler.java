package il.co.ilrd.iosystem;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;
import java.util.List;

import il.co.ilrd.observer.Callback;

public class BackUpFileHandler {
    private final Callback<String> callback = new Callback<>(str -> {
        update(str);
    }, () -> {
    });
    private final Path originalFilePath;
    private final FileCRUD backUpFileCrud;
    private List<String> lines;

    public BackUpFileHandler(String originalFile, String backUpFile) {
        originalFilePath = Paths.get(originalFile);
        try (FileCRUD fd = new FileCRUD(originalFile, false)) {
        } catch (Exception e) {
            e.printStackTrace();
        }

        backUpFileCrud = new FileCRUD(backUpFile, true);
        try {
            lines = Files.readAllLines(originalFilePath);
        } catch (IOException e) {
            e.printStackTrace();
        }
        for (int i = 0; i < lines.size(); ++i) {
            backUpFileCrud.create(lines.get(i));
        }
    }

    public void update(String pathAndEntryState) {
        if (!pathAndEntryState.split(" ")[0].equals(originalFilePath.getFileName().toString())) {
            return;
        }
        try {
            lines = Files.readAllLines(originalFilePath);
        } catch (IOException e) {
            e.printStackTrace();
        }
        if (StandardWatchEventKinds.ENTRY_MODIFY.name().equals(pathAndEntryState.split(" ")[1])) {

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
