package il.co.ilrd.jdbc;

import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import il.co.ilrd.iosystem.CRUD;

public class SQLCRUD implements CRUD<String, String> {

    private final Connection con;
    private final List<Integer> primaryKeyColIndexesList;
    private final int numberOfCols;
    private final PreparedStatement pstmtCreate;
    private final PreparedStatement pstmtRead;
    private final PreparedStatement pstmtDelete;

    public SQLCRUD(String url, String username, String password, String tableName)
            throws ClassNotFoundException, SQLException {
        String driverClassName = "com.mysql.cj.jdbc.Driver";
        Class.forName(driverClassName);

        con = DriverManager.getConnection(
                url, username, password);

        Statement statement = con.createStatement();
        DatabaseMetaData dbmetada = con.getMetaData();
        ResultSet resultSet = dbmetada.getPrimaryKeys(null, null, tableName);

        List<String> primaryKeyListNames = new ArrayList<>();
        while (resultSet.next()) {
            primaryKeyListNames.add(resultSet.getString("COLUMN_NAME"));
        }
        resultSet.close();
        ResultSet rs = statement.executeQuery("SELECT * FROM " + tableName);
        ResultSetMetaData rsMetaData = rs.getMetaData();
        numberOfCols = rsMetaData.getColumnCount();

        primaryKeyColIndexesList = new ArrayList<>();

        for (String pkName : primaryKeyListNames) {
            for (int i = 1; i <= numberOfCols; ++i) {
                if (pkName.equals(rsMetaData.getColumnName(i))) {
                    primaryKeyColIndexesList.add(i);
                }
            }
        }
        /* INSERT IGNORE INTO computers VALUES(?, ?,?,?,?,?,?) */
        StringBuilder stringCreate = new StringBuilder("INSERT IGNORE INTO " + tableName + " VALUES(");
        for (int i = 0; i < numberOfCols; ++i) {
            stringCreate.append("?");
            if (i != numberOfCols - 1) {
                stringCreate.append(", ");
            }
        }
        stringCreate.append(")");

        pstmtCreate = con.prepareStatement(stringCreate.toString());

        /* SELECT * FROM manu WHERE manuID = ? AND manuName = ?*/
        StringBuilder stringRead = new StringBuilder("SELECT * FROM " + tableName + " WHERE ");
        for (int i = 0; i < primaryKeyListNames.size(); ++i) {

            stringRead.append(primaryKeyListNames.get(i) + " = ?");

            if (i != primaryKeyListNames.size() - 1) {
                stringRead.append(" AND ");
            }
        }

        pstmtRead = con.prepareStatement(stringRead.toString());

        StringBuilder stringDelete = new StringBuilder("DELETE FROM " + tableName + " WHERE ");
        for (int i = 0; i < primaryKeyListNames.size(); ++i) {

            stringDelete.append(primaryKeyListNames.get(i) + " = ?");

            if (i != primaryKeyListNames.size() - 1) {
                stringDelete.append(" AND ");
            }
        }

        pstmtDelete = con.prepareStatement(stringDelete.toString());

        rs.close();
        statement.close();
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

        try (SQLCRUD docrud = new SQLCRUD("jdbc:mysql://localhost:3306/computerStore", "root", "",
                "manufacturers")) {
            docrud.create("2 Dell");
            System.out.println(docrud.read("2"));
            docrud.delete("2");
        } catch (Exception e) {

            e.printStackTrace();
        }
        try (SQLCRUD docrud1 = new SQLCRUD("jdbc:mysql://localhost:3306/computerStore", "root", "",
                "computer")) {
            // docrud1.create("2 500 600 700 800 0 0 800 0");
            // System.out.println(docrud1.read("2 0"));
            // docrud1.update("2 0", "2 709990 10000 700 800 0 0 800 0");
            docrud1.delete("2 0");
        } catch (Exception e) {

            e.printStackTrace();
        }
    }

    @Override
    public void close() throws Exception {
        pstmtCreate.close();
        pstmtRead.close();
        pstmtDelete.close();
        con.close();
    }

    /*pk col2 col3 pk col5 */
    /* JUST SPACE!!!!!!!! */
    @Override
    public String create(String data) {
        StringBuilder keys = new StringBuilder();
        String[] dataAsArray = data.split(" ");
        for (int keyIndex : primaryKeyColIndexesList) {
            keys.append(dataAsArray[keyIndex - 1]);
        }
        try {
            for (int i = 0; i < dataAsArray.length; ++i) {
                pstmtCreate.setString(i + 1, dataAsArray[i]);
            }
            pstmtCreate.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return keys.toString();
    }

    @Override
    public String read(String key) {
        String[] keyAsArray = key.split(" ");
        try {
            for (int i = 0; i < keyAsArray.length; ++i) {
                pstmtRead.setString(i + 1, keyAsArray[i]);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        StringBuilder result = new StringBuilder();
        try (ResultSet resultSet = pstmtRead.executeQuery()) {
            while (resultSet.next()) {
                for (int i = 1; i <= numberOfCols; ++i) {
                    result.append(resultSet.getString(i));
                    if (i != numberOfCols) {
                        result.append(" ");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return result.toString();
    }

    @Override
    public void update(String key, String data) {
        delete(key);
        create(data);
    }

    @Override
    public void delete(String key) {
        String[] keyAsArray = key.split(" ");
        try {
            for (int i = 0; i < keyAsArray.length; ++i) {
                pstmtDelete.setString(i + 1, keyAsArray[i]);
            }
            pstmtDelete.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
