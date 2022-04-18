package il.co.ilrd.jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class DataObjectCRUD {
    public static void whatIsolationLevelMySql() throws ClassNotFoundException, SQLException {
        String driverClassName = "com.mysql.cj.jdbc.Driver";
        String url = "jdbc:mysql://localhost:3306/computerStore";
        String username = "root";
        String password = "";
        /* String query = "SELECT is_read_committed_snapshot_on FROM sys.databases WHERE name = DB_NAME()"; */
        String query = "SELECT modelID, procssorSpeed,HDspace FROM computer WHERE price < 2500;";

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
            System.out.println(rs.getString("modelID"));
            System.out.println(rs.getString("HDspace"));
        }

        // Closing the connection as per the
        // requirement with connection is completed
        con.close();
    }

    public static void main(String[] args) {
        try {
            whatIsolationLevelMySql();
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
    }
}
