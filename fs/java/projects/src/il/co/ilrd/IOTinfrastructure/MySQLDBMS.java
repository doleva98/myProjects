package il.co.ilrd.IOTinfrastructure;

import java.util.Arrays;

import il.co.ilrd.hashmap.Pair;
import il.co.ilrd.jdbc.SQLCRUD;

public class MySQLDBMS implements IOTDBMS {
    private final String url;
    private final String username;
    private final String password;

    public MySQLDBMS(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;

    }

    @Override
    public void companyAdd(Pair<String, Responder> pair) {
        /* addressID INT,
        zipcode INT NOT NULL,
        city VARCHAR(250) NOT NULL,
        street VARCHAR(250) NOT NULL,
        
        contactID INT,
        phoneNumber INT NOT NULL,
        contactPersonName VARCHAR(250) NOT NULL,
        email VARCHAR(250) NOT NULL,
        
        companyID INT,
        company_name VARCHAR(250) NOT NULL,
        contactID INT NOT NULL UNIQUE,
        addressID INT NOT NULL,
        
        payID INT,
        companyID INT NOT NULL,
        creditDetails VARCHAR(250) NOT NULL,*/

        String[] data = pair.getKey().split(" ");
        Responder respond = pair.getValue();
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "Addresses")) {
            crud.create(String.join(" ", Arrays.copyOfRange(data, 0, 4)));
        } catch (Exception e) {
            respond.respond("address cant be created");
        }
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "ContactPerson")) {
            crud.create(String.join(" ", Arrays.copyOfRange(data, 4, 8)));
        } catch (Exception e) {
            respond.respond("contact person cant be created");
        }
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "Companies")) {
            crud.create(String.join(" ", Arrays.copyOfRange(data, 8, 12)));
        } catch (Exception e) {
            respond.respond("Companies cant be created");
        }
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "Payments")) {
            crud.create(String.join(" ", Arrays.copyOfRange(data, 12, 15)));
        } catch (Exception e) {
            respond.respond("Companies cant be created");
        }
        respond.respond("Company is added successfully");
    }

    @Override
    public void productAdd(Pair<String, Responder> pair) {
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "Companies")) {
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void IOTAdd(Pair<String, Responder> pair) {
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "Companies")) {
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void IOTUpdate(Pair<String, Responder> pair) {
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "Companies")) {
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
