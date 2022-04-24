package il.co.ilrd.IOTinfrastructure;

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
        try (SQLCRUD crud = new SQLCRUD(url, username, password, "Companies")) {
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void companyAdd(Pair<String, Responder> pair) {

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
