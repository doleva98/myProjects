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
    private int currSize = 0;

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
        con.close();
    }

    @Override
    public Integer create(String data) {
        // Obtain a statement
        Statement st;
        try {
            st = con.createStatement();
            StringBuilder query = new StringBuilder("INSERT INTO " + tableName + " VALUES (");
            String[] dataArray = data.split(" ");
            for (int i = 0; i < dataArray.length - 1; ++i) {
                query.append(dataArray[i] + ", ");
            }
            query.append(dataArray[dataArray.length - 1] + ")");
            st.executeUpdate(query.toString());
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ++currSize;
    }

    @Override
    public String read(Integer key) {
        StringBuilder res = null;
        try (Statement st = con.createStatement()) {
            String query = "SELECT * FROM " + tableName;

            ResultSet rs = st.executeQuery(query);

            for (int i = 1; i < key; ++i, rs.next()) {
            }

            res = new StringBuilder();
            int numOfCols = rs.getMetaData().getColumnCount();
            for (int i = 1; i < numOfCols; ++i) {
                res.append(rs.getString(i));
                if (i != numOfCols - 1) {
                    res.append(" ");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return res.toString();
    }

    @Override
    public void update(Integer key, String data) {
    }

    @Override
    public void delete(Integer key) {
    }
}
