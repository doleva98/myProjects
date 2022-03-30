package il.co.ilrd.iosystem;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.Objects;

class FileCRUD implements CRUD<Integer, String> {
    private final String path;
    private final BufferedWriter bw;

    public FileCRUD(String path, boolean cleanFile) throws IOException {
        Objects.requireNonNull(path);
        this.path = path;
        bw = new BufferedWriter(new FileWriter(path, cleanFile));
    }

    @Override
    public void close() throws Exception {
        bw.close();
    }

    @Override
    public Integer create(String data) throws IOException {
        if (size() != 0) {
            bw.newLine();
        }
        bw.write(data);
        bw.flush();
        return size() - 1;
    }

    @Override
    public String read(Integer key) throws IOException {
        return Files.readAllLines(Paths.get(path)).get(key).trim();
    }

    @Override
    public void update(Integer key, String data) throws IOException, ClassNotFoundException {
        List<String> list = Files.readAllLines(Paths.get(path));
        list.set(key, data);
        writeToCleanFile(list);
    }

    @Override
    public void delete(Integer key) throws IOException, ClassNotFoundException {
        List<String> list = Files.readAllLines(Paths.get(path));
        list.remove((int) key);
        writeToCleanFile(list);
    }

    public int size() throws IOException {
        return Files.readAllLines(Paths.get(path)).size();
    }

    private void writeToCleanFile(List<String> list) throws IOException, ClassNotFoundException {
        cleanFile();
        for (String str : list) {
            create(str);
        }
    }

    private void cleanFile() throws IOException, ClassNotFoundException {
        BufferedWriter bw1 = new BufferedWriter(new FileWriter(path));
        bw1.close();
        delete(0);
    }
}
