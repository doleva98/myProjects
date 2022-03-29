package il.co.ilrd.iosystem;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

class FileCRUD implements CRUD<Integer, String> {
    private BufferedWriter bw = null;
    private BufferedReader br = null;
    private int size = 0;

    public FileCRUD(String path) throws IOException {
        bw = new BufferedWriter(new FileWriter(path));
        br = new BufferedReader(new FileReader(path));
        size = (int) br.lines().count();
    }

    @Override
    public void close() throws Exception {
        bw.close();
        br.close();
    }

    @Override
    public Integer create(String data) throws IOException {
        bw.write(data);
        return ++size;
    }

    @Override
    public String read(Integer key) throws IOException {
        return br.readLine();
    }

    @Override
    public void update(Integer key, String data) throws IOException, ClassNotFoundException {

    }

    @Override
    public void delete(Integer key) throws IOException, ClassNotFoundException {

    }

}
