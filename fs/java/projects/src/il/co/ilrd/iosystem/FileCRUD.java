package il.co.ilrd.iosystem;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class FileCRUD implements CRUD<Integer, String> {
    private List<String> lines = new ArrayList<>();
    private final Path path;

    public FileCRUD(String path, boolean cleanFile) {
        Objects.requireNonNull(path);
        this.path = Paths.get(path);
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(path.toString(), !cleanFile))) {
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            lines = Files.readAllLines(Paths.get(path));
        } catch (IOException e1) {
            e1.printStackTrace();
        }
        /*  if (lines.size() != 0 && cleanFile) {
            lines.clear();
            try {
                Files.write(this.path, lines);
            } catch (IOException e) {
                e.printStackTrace();
            }
        } */
    }

    @Override
    public void close() throws Exception {
    }

    @Override
    public Integer create(String data) {
        lines.add(data);
        try {
            Files.write(path, lines);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return size() - 1;
    }

    @Override
    public String read(Integer key) {
        return lines.get(key);
    }

    @Override
    public void update(Integer key, String data) {
        lines.set(key, data);
        try {
            Files.write(path, lines);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void delete(Integer key) {
        lines.remove((int) key);
        try {
            Files.write(path, lines);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public int size() {
        return lines.size();
    }
}
