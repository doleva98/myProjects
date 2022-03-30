package il.co.ilrd.iosystem;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.Objects;

class FileCRUD implements CRUD<Integer, String> {
    private final List<String> lines;
    private final Path path;

    public FileCRUD(String path, boolean dontCleanFile) throws IOException, ClassNotFoundException {
        Objects.requireNonNull(path);
        this.path = Paths.get(path);
        lines = Files.readAllLines(Paths.get(path));
        if (!dontCleanFile) {
            cleanFile();
        }
    }

    @Override
    public void close() throws Exception {
    }

    @Override
    public Integer create(String data) throws IOException {
        lines.add(data);
        Files.write(path, lines);
        return size() - 1;
    }

    @Override
    public String read(Integer key) throws IOException {
        return lines.get(key);
    }

    @Override
    public void update(Integer key, String data) throws IOException, ClassNotFoundException {
        lines.set(key, data);
        Files.write(path, lines);
    }

    @Override
    public void delete(Integer key) throws IOException, ClassNotFoundException {
        lines.remove((int) key);
        Files.write(path, lines);
    }

    public int size() throws IOException {
        return lines.size();
    }

    private void cleanFile() throws IOException, ClassNotFoundException {
        while (!lines.isEmpty()) {
            delete(0);
        }
    }
}
