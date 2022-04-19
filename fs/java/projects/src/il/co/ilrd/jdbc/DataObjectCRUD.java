package il.co.ilrd.jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import il.co.ilrd.iosystem.CRUD;

public class DataObjectCRUD implements CRUD<Integer, String> {

    private Connection con = null;
    private String tableName = null;

    public DataObjectCRUD(String url, String username, String password, String tableName)
            throws ClassNotFoundException, SQLException {
        String driverClassName = "com.mysql.cj.jdbc.Driver";
        Class.forName(driverClassName);

        con = DriverManager.getConnection(
                url, username, password);
        this.tableName = tableName;
    }

    public static void whatIsolationLevelMySql() throws ClassNotFoundException, SQLException {
        String driverClassName = "com.mysql.cj.jdbc.Driver";
        String url = "jdbc:mysql://localhost:3306/sys";
        String username = "root";
        String password = "";
        String query = "SELECT @@transaction_ISOLATION;";

        // Load driver class
        Class.forName(driverClassName);

        // Obtain a connection
        Connection con = DriverManager.getConnection(
                url, username, password);

        // Obtain a statement
        Statement st = con.createStatement();

        // Step 4: Executing the query and storing the
        // result
        ResultSet rs = st.executeQuery(query);

        // Step 5: Processing the results
        while (rs.next()) {
            System.out.println(rs.getString(1));
        }

        // Closing the connection as per the
        // requirement with connection is completed
        con.close();
    }

    public static void main(String[] args) {
        /*   try {
            whatIsolationLevelMySql();
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        } */

        try (DataObjectCRUD docrud = new DataObjectCRUD("jdbc:mysql://localhost:3306/sys", "root", "", null)) {
        } catch (Exception e) {

            e.printStackTrace();
        }
    }

    @Override
    public void close() throws Exception {
    }

    @Override
    public Integer create(String query) {
        // Obtain a statement
        Statement st;
        try {
            st = con.createStatement();
            ResultSet rs = st.executeQuery(query);
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        // Step 4: Executing the query and storing the
        // result
        return null;
    }

    @Override
    public String read(Integer key) {
        return null;
    }

    @Override
    public void update(Integer key, String query) {
    }

    @Override
    public void delete(Integer key) {
    }
}
