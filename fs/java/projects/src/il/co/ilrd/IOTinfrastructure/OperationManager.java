package il.co.ilrd.IOTinfrastructure;

import il.co.ilrd.factory.Factory;
import il.co.ilrd.hashmap.Pair;
import il.co.ilrd.iosystem.FileCRUD;
import il.co.ilrd.jdbc.DataObjectCRUD;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/* key company_name product_name line*/
public class OperationManager {
    private final Factory<Command, Pair<String, Responder>, String> commandFactory = new Factory<>();
    private final ExecutorService executor;
    private final String databasePath;

    public OperationManager(String url, String username, String password) {
        databasePath = url + " " + username + " " + password;
        executor = Executors.newCachedThreadPool();
        commandFactory.add("CompanyRegisterCommand", CompanyRegisterCommand::new);
        commandFactory.add("ProductRegisterCommand", ProductRegisterCommand::new);
        commandFactory.add("IOTRegisterCommand", IOTRegisterCommand::new);
        commandFactory.add("IOTUpdateCommand", IOTUpdateCommand::new);
        commandFactory.add("ping", PingCommand::new);
        commandFactory.add("AddressRegisterCommand", AddressRegisterCommand::new);
        commandFactory.add("ContactPersonRegisterCommand", ContactPersonRegisterCommand::new);
        commandFactory.add("PaymentRegisterCommand", PaymentRegisterCommand::new);
    }

    public void handleRequest(String request, Responder response) {
        /* request = key + " "  + data*/

        executor.submit(commandFactory.create(request.split(" ")[0], Pair.of(databasePath + request.substring(
                request.split(" ")[0].length()), response)));

    }

    public void stop() {
        executor.shutdown();
    }
}

class CompanyRegisterCommand implements Command {
    private final String data;
    private final Responder responder;

    /* data[0] = path, data[1] = folder(company) name */
    public CompanyRegisterCommand(Pair<String, Responder> pair) {
        this.data = pair.getKey();
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        String[] dataArray = data.split(" ", 4);
        final String url = dataArray[0];
        final String username = dataArray[1];
        final String password = dataArray[2];
        final String inputForTable = dataArray[3];
        try (DataObjectCRUD docrud = new DataObjectCRUD(
                url,
                username,
                password,
                "Companies")) {
            docrud.create(inputForTable);
        } catch (Exception e) {
            System.out.println("Company is not found!");
            responder.respond("Company is not found!");
        }
        System.out.println("Company is created successfully");
        responder.respond("Company is created successfully");
    }
}

class ProductRegisterCommand implements Command {
    private final String data;
    private final Responder responder;

    /* data[0] = path, data[1] = folder(company) name */
    public ProductRegisterCommand(Pair<String, Responder> pair) {
        this.data = pair.getKey();
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        String[] dataArray = data.split(" ", 4);
        final String url = dataArray[0];
        final String username = dataArray[1];
        final String password = dataArray[2];
        final String inputForTable = dataArray[3];
        try (DataObjectCRUD docrud = new DataObjectCRUD(
                url,
                username,
                password,
                "Products")) {
            docrud.create(inputForTable);
        } catch (Exception e) {
            System.out.println("Products is not added!");
            responder.respond("Products is not added!");
        }
        System.out.println("Products is created successfully");
        responder.respond("Products is created successfully");
    }
}

class IOTRegisterCommand implements Command {
    private final String data;
    private final Responder responder;

    /* data[0] = path, data[1] = folder(company) name */
    public IOTRegisterCommand(Pair<String, Responder> pair) {
        this.data = pair.getKey();
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        String[] dataArray = data.split(" ", 4);
        final String url = dataArray[0];
        final String username = dataArray[1];
        final String password = dataArray[2];
        final String inputForTable = dataArray[3];
        try (DataObjectCRUD docrud = new DataObjectCRUD(
                url,
                username,
                password,
                "IOT")) {
            docrud.create(inputForTable);
        } catch (Exception e) {
            System.out.println("IOT is not added!");
            responder.respond("IOT is not added!");
        }
        System.out.println("IOT is created successfully");
        responder.respond("IOT is created successfully");
    }
}

class IOTUpdateCommand implements Command {
    private final String data;
    private final Responder responder;

    /* data[0] = path, data[1] = folder(company) name */
    public IOTUpdateCommand(Pair<String, Responder> pair) {
        this.data = pair.getKey();
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        String[] dataArray = data.split(" ", 4);
        final String url = dataArray[0];
        final String username = dataArray[1];
        final String password = dataArray[2];
        final String inputForTable = dataArray[3];
        try (DataObjectCRUD docrud = new DataObjectCRUD(
                url,
                username,
                password,
                "IOTLog")) {
            docrud.create(inputForTable);
        } catch (Exception e) {
            System.out.println("IOTLog is not added!");
            responder.respond("IOTLog is not added!");
        }
        System.out.println("IOTLog is created successfully");
        responder.respond("IOTLog is created successfully");
    }
}

class PingCommand implements Command {
    private Responder responder;

    /* data[0] = path, data[1] = folder(company) name data[2] = filename(product name)*/

    public PingCommand(Pair<String, Responder> pair) {
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        responder.respond("pong");
    }
}

class AddressRegisterCommand implements Command {
    private final String data;
    private final Responder responder;

    /* data[0] = path, data[1] = folder(company) name */
    public AddressRegisterCommand(Pair<String, Responder> pair) {
        this.data = pair.getKey();
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        String[] dataArray = data.split(" ", 4);
        final String url = dataArray[0];
        final String username = dataArray[1];
        final String password = dataArray[2];
        final String inputForTable = dataArray[3];
        try (DataObjectCRUD docrud = new DataObjectCRUD(
                url,
                username,
                password,
                "Addresses")) {
            docrud.create(inputForTable);
        } catch (Exception e) {
            System.out.println("address is not added!");
            responder.respond("address is not added!");
        }
        System.out.println("address is created successfully");
        responder.respond("address is created successfully");
    }
}

class ContactPersonRegisterCommand implements Command {
    private final String data;
    private final Responder responder;

    /* data[0] = path, data[1] = folder(company) name */
    public ContactPersonRegisterCommand(Pair<String, Responder> pair) {
        this.data = pair.getKey();
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        String[] dataArray = data.split(" ", 4);
        final String url = dataArray[0];
        final String username = dataArray[1];
        final String password = dataArray[2];
        final String inputForTable = dataArray[3];
        try (DataObjectCRUD docrud = new DataObjectCRUD(
                url,
                username,
                password,
                "ContactPerson")) {
            docrud.create(inputForTable);
        } catch (Exception e) {
            System.out.println("ContactPerson is not added!");
            responder.respond("ContactPerson is not added!");
        }
        System.out.println("ContactPerson is created successfully");
        responder.respond("ContactPerson is created successfully");
    }
}

class PaymentRegisterCommand implements Command {
    private final String data;
    private final Responder responder;

    /* data[0] = path, data[1] = folder(company) name */
    public PaymentRegisterCommand(Pair<String, Responder> pair) {
        this.data = pair.getKey();
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        String[] dataArray = data.split(" ", 4);
        final String url = dataArray[0];
        final String username = dataArray[1];
        final String password = dataArray[2];
        final String inputForTable = dataArray[3];
        try (DataObjectCRUD docrud = new DataObjectCRUD(
                url,
                username,
                password,
                "Payments")) {
            docrud.create(inputForTable);
        } catch (Exception e) {
            System.out.println("Payments is not added!");
            responder.respond("Payments is not added!");
        }
        System.out.println("Payments is created successfully");
        responder.respond("Payments is created successfully");
    }
}