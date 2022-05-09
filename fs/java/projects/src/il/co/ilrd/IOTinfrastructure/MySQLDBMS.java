package il.co.ilrd.IOTinfrastructure;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Arrays;

import il.co.ilrd.hashmap.Pair;
import il.co.ilrd.jdbc.SQLCRUD;

public class MySQLDBMS implements IOTDBMS {
    private String url;
    private final String username;
    private final String password;

    public MySQLDBMS(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
        createDataBase();
    }

    private void createDataBase() {
        String driverClassName = "com.mysql.cj.jdbc.Driver";
        try {
            Class.forName(driverClassName);
            try (Connection con = DriverManager.getConnection(
                    url, username, password)) {
                Statement statement = con.createStatement();
                statement.addBatch("CREATE DATABASE IF NOT EXISTS IOTInfrastructure");
                statement.addBatch("USE IOTInfrastructure");
                statement.addBatch(
                        "CREATE TABLE IF NOT EXISTS Addresses( addressID INT, zipcode INT NOT NULL, city VARCHAR(250) NOT NULL, street VARCHAR(250) NOT NULL, PRIMARY KEY(addressID))");
                statement.addBatch(
                        "CREATE TABLE IF NOT EXISTS ContactPerson( contactID INT, phoneNumber INT NOT NULL, contactPersonName VARCHAR(250) NOT NULL, email VARCHAR(250) NOT NULL, PRIMARY KEY(contactID))");
                statement.addBatch(
                        "CREATE TABLE IF NOT EXISTS Companies( companyID INT, company_name VARCHAR(250) NOT NULL, contactID INT NOT NULL UNIQUE, addressID INT NOT NULL, PRIMARY KEY(companyID), FOREIGN KEY(addressID) REFERENCES Addresses(addressID) ON DELETE CASCADE, FOREIGN KEY(contactID) REFERENCES ContactPerson(contactID) ON DELETE CASCADE)");
                statement.addBatch(
                        "CREATE TABLE IF NOT EXISTS Products( productID INT, productname VARCHAR(250) NOT NULL, companyID INT NOT NULL, PRIMARY KEY(productID, companyID), FOREIGN KEY(companyID) REFERENCES Companies(companyID) ON DELETE CASCADE)");
                statement.addBatch(
                        "CREATE TABLE IF NOT EXISTS IOT( IOTID INT, serialNum INT, productID INT NOT NULL, PRIMARY KEY(IOTID, serialNum), FOREIGN KEY(productID) REFERENCES Products(productID) ON DELETE CASCADE)");
                statement.addBatch(
                        "CREATE TABLE IF NOT EXISTS IOTLog( logNumber INT, IOTID INT NOT NULL, logDate DATETIME DEFAULT CURRENT_TIMESTAMP, logData VARCHAR(250) NOT NULL, PRIMARY KEY(logNumber), FOREIGN KEY(IOTID) REFERENCES IOT(IOTID) ON DELETE CASCADE)");
                statement.addBatch(
                        "CREATE TABLE IF NOT EXISTS Payments( payID INT, companyID INT NOT NULL, creditDetails VARCHAR(250) NOT NULL, PRIMARY KEY(payID), FOREIGN KEY(companyID) REFERENCES Companies(companyID) ON DELETE CASCADE)");
                statement.executeBatch();
                url += "IOTInfrastructure";
            } catch (SQLException e) {
                e.printStackTrace();
            }
        } catch (ClassNotFoundException e1) {
            e1.printStackTrace();
        }

    }

    @Override
    public void companyAdd(Pair<String, Responder> pair) {
        /*
         * addressID INT,
         * zipcode INT NOT NULL,
         * city VARCHAR(250) NOT NULL,
         * street VARCHAR(250) NOT NULL,
         * 
         * contactID INT,
         * phoneNumber INT NOT NULL,
         * contactPersonName VARCHAR(250) NOT NULL,
         * email VARCHAR(250) NOT NULL,
         * 
         * companyID INT,
         * company_name VARCHAR(250) NOT NULL,
         * contactID INT NOT NULL UNIQUE,
         * addressID INT NOT NULL,
         * 
         * payID INT,
         * companyID INT NOT NULL,
         * creditDetails VARCHAR(250) NOT NULL,
         */
        String[] data = pair.getKey().split(" ");
        Responder respond = pair.getValue();
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "Addresses")) {
            String key = crud.create(String.join(" ", Arrays.copyOfRange(data, 1, 5)));
            if (!crud.read(key).equals(String.join(" ", Arrays.copyOfRange(data, 1, 5)))) {
                respond.respond("address cant be created");
            }
        } catch (Exception e) {
            respond.respond("address cant be created");
        }
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "ContactPerson")) {
            String key = crud.create(String.join(" ", Arrays.copyOfRange(data, 5, 9)));
            if (!crud.read(key).equals(String.join(" ", Arrays.copyOfRange(data, 5, 9)))) {
                // respond.respond("ContactPerson cant be created");
            }
        } catch (Exception e) {
            respond.respond("contact person cant be created");
        }
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "Companies")) {
            String key = crud.create(String.join(" ", Arrays.copyOfRange(data, 9, 13)));
            if (!crud.read(key).equals(String.join(" ", Arrays.copyOfRange(data, 9, 13)))) {
                respond.respond("Companies cant be created");
            }

        } catch (Exception e) {
            respond.respond("Companies cant be created");
        }
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "Payments")) {
            String key = crud.create(String.join(" ", Arrays.copyOfRange(data, 13, 16)));
            if (!crud.read(key).equals(String.join(" ", Arrays.copyOfRange(data, 13, 16)))) {
                respond.respond("Payments cant be created");
            } else {
                respond.respond("Company is added successfully");
            }
        } catch (Exception e) {
            respond.respond("Payments cant be created");
        }
    }

    @Override
    public void productAdd(Pair<String, Responder> pair) {
        /*
         * productID INT,
         * productname VARCHAR(250) NOT NULL,
         * companyID INT NOT NULL,
         */
        String[] data = pair.getKey().split(" ");
        Responder respond = pair.getValue();
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "Products")) {
            String key = crud.create(String.join(" ", Arrays.copyOfRange(data, 1, 4)));
            if (!crud.read(key).equals(String.join(" ", Arrays.copyOfRange(data, 1, 4)))) {
                respond.respond("Products cant be created");
            } else {
                respond.respond("product is added successfully");
            }
        } catch (Exception e) {
            respond.respond("product cant be created");
        }
    }

    @Override
    public void IOTAdd(Pair<String, Responder> pair) {
        String[] data = pair.getKey().split(" ");
        Responder respond = pair.getValue();
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "IOT")) {
            String key = crud.create(String.join(" ", Arrays.copyOfRange(data, 1, 4)));
            if (!crud.read(key).equals(String.join(" ", Arrays.copyOfRange(data, 1, 4)))) {
                respond.respond("IOT cant be created");
            } else {
                respond.respond("IOT is added successfully");
            }
        } catch (Exception e) {
            respond.respond("IOT cant be created");
        }
    }

    @Override
    public void IOTUpdate(Pair<String, Responder> pair) {
        String[] data = pair.getKey().split(" ");
        Responder respond = pair.getValue();
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "IOTLog")) {
            String key = crud.create(String.join(" ", Arrays.copyOfRange(data, 1, 5)));
            if (!crud.read(key).equals(String.join(" ", Arrays.copyOfRange(data, 1, 5)))) {
                respond.respond("IOTLog cant be created");
            } else {
                respond.respond("IOTLog is added successfully");
            }
        } catch (Exception e) {
            respond.respond("IOTLog cant be created");
        }
    }

}
