package il.co.ilrd.jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class DataObjectCRUD {

    private String url = "jdbc:mysql://localhost:3306/sys";
    private String username = "root";
    private String password = "";

    public DataObjectCRUD(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
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

        DataObjectCRUD docrud = new DataObjectCRUD("jdbc:mysql://localhost:3306/sys", "root", "");
    }
}
