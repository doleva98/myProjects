package il.co.ilrd.IOTinfrastructure;

import il.co.ilrd.factory.Factory;
import il.co.ilrd.hashmap.Pair;
import il.co.ilrd.iosystem.FileCRUD;

import java.io.File;
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

    public OperationManager(String databasePath) {
        this.databasePath = databasePath;
        executor = Executors.newCachedThreadPool();
        commandFactory.add("CompanyRegisterCommand", CompanyRegisterCommand::new);
        commandFactory.add("ProductRegisterCommand", ProductRegisterCommand::new);
        commandFactory.add("IOTRegisterCommand", IOTRegisterCommand::new);
        commandFactory.add("IOTUpdateCommand", IOTUpdateCommand::new);
        commandFactory.add("ping", PingCommand::new);
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
    private String data;
    private Responder responder;

    /* data[0] = path, data[1] = folder(company) name */
    public CompanyRegisterCommand(Pair<String, Responder> pair) {
        this.data = pair.getKey();
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        /* open folders */
        File f1 = new File(data.split(" ")[0] + "\\" + data.split(" ")[1]);
        //Creating a folder using mkdir() method  
        if (f1.mkdir()) {
            System.out.println("Folder is created successfully");
            responder.respond("Folder is created successfully");
        } else {
            System.out.println("Folder is not found!");
            responder.respond("Folder is not found!");
        }
    }
}

class ProductRegisterCommand implements Command {
    private String data;
    private Responder responder;

    /* data[0] = path, data[1] = folder(company) name data[2] = filename(product name)*/

    public ProductRegisterCommand(Pair<String, Responder> pair) {
        this.data = pair.getKey();
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        String path = data.split(" ")[0] + "\\" + data.split(" ")[1] + "\\" + data
                .split(" ")[2];
        /* creates a new file in folder */
        try (FileCRUD fileCRUD = new FileCRUD(path, true)) {
            System.out.println("file is created");
            responder.respond("file is created");
        } catch (Exception e) {
            System.out.println("there was an exception create a new file");
            responder.respond("there was an exception create a new file");
            e.printStackTrace();
        }
    }
}

class IOTRegisterCommand implements Command {
    private String data;
    private Responder responder;

    /* data[0] = path, data[1] = folder(company) name data[2] = filename(product name)
        data[3...] product line*/
    /* product line = "id" + " " + "iot name" + " name of user" */
    public IOTRegisterCommand(Pair<String, Responder> pair) {
        this.data = pair.getKey();
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        /* create a line in product file */
        String path = data.split(" ")[0] + "\\" + data.split(" ")[1] + "\\" + data
                .split(" ")[2];
        String dataToWrite = data.substring(data.split(" ")[0].length() + 1 + data.split(" ")[1].length() + 1
                + data.split(" ")[2].length() + 1);

        /* if not file found respond fail */
        try (FileCRUD fileCRUD = new FileCRUD(path, false)) {
            fileCRUD.create(dataToWrite);
            System.out.println("line is added to file");
            responder.respond("line is added to file");
        } catch (Exception e) {
            System.out.println("there was an exception create a new file");
            responder.respond("there was an exception create a new file");
            e.printStackTrace();
        }
    }
}

class IOTUpdateCommand implements Command {
    private String data;
    private Responder responder;

    /* data is company name + " "  + product name + " " + product line */
    public IOTUpdateCommand(Pair<String, Responder> pair) {
        this.data = pair.getKey();
        this.responder = pair.getValue();
    }

    @Override
    public void run() {
        /* update a line in product file */
        String path = data.split(" ")[0] + "\\" + data.split(" ")[1] + "\\" + data
                .split(" ")[2];
        String dataToWrite = data.substring(data.split(" ")[0].length() + 1 + data.split(" ")[1].length() + 1
                + data.split(" ")[2].length() + 1);

        try (FileCRUD fileCRUD = new FileCRUD(path, false)) {

            String id = data.split(" ")[3];
            List<String> lines = Files.readAllLines(Paths.get(path));

            for (int i = 0; i < lines.size(); ++i) {
                if (lines.get(i).split(" ")[0].equals(id)) {
                    fileCRUD.update(i, dataToWrite);
                }
            }

            System.out.println("line is updated in the file");
            responder.respond("line is updated in the file");
        } catch (Exception e) {
            System.out.println("there was an exception create a new file");
            responder.respond("there was an exception create a new file");
            e.printStackTrace();
        }

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