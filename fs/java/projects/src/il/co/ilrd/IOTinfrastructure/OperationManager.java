package il.co.ilrd.IOTinfrastructure;

import il.co.ilrd.factory.Factory;
import il.co.ilrd.hashmap.Pair;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/* key company_name product_name line*/
public class OperationManager {
    private final ExecutorService executor;
    private final IOTDBMS dbms;
    private final Factory<Command, FactoryData, String> commandFactory;

    public OperationManager(IOTDBMS dbms, Factory<Command, FactoryData, String> commandFactory) {
        this.dbms = dbms;
        executor = Executors.newCachedThreadPool();
        this.commandFactory = commandFactory;
    }

    public void handleRequest(String request, Responder response) {
        /* request = key + " "  + data*/

        executor.submit(commandFactory.create(request.split(" ")[0], new FactoryData(request.substring(
                request.split(" ")[0].length()), response, dbms)));

    }

    public void stop() {
        executor.shutdown();
    }
}

class CompanyRegisterCommand implements Command {
    private final Pair<String, Responder> pair;
    private final IOTDBMS dbms;

    /* data[0] = path, data[1] = folder(company) name */
    public CompanyRegisterCommand(FactoryData factoryData) {
        pair = Pair.of(factoryData.getData(), factoryData.getResponder());
        dbms = factoryData.getDbms();
    }

    @Override
    public void run() {
        dbms.companyAdd(pair);
    }
}

class ProductRegisterCommand implements Command {
    private final Pair<String, Responder> pair;
    private final IOTDBMS dbms;

    /* data[0] = path, data[1] = folder(company) name */
    public ProductRegisterCommand(FactoryData factoryData) {
        pair = Pair.of(factoryData.getData(), factoryData.getResponder());
        dbms = factoryData.getDbms();
    }

    @Override
    public void run() {
        dbms.productAdd(pair);
    }
}

class IOTRegisterCommand implements Command {
    private final Pair<String, Responder> pair;
    private final IOTDBMS dbms;

    /* data[0] = path, data[1] = folder(company) name */
    public IOTRegisterCommand(FactoryData factoryData) {
        pair = Pair.of(factoryData.getData(), factoryData.getResponder());
        dbms = factoryData.getDbms();
    }

    @Override
    public void run() {
        dbms.IOTAdd(pair);
    }
}

class IOTUpdateCommand implements Command {
    private final Pair<String, Responder> pair;
    private final IOTDBMS dbms;

    /* data[0] = path, data[1] = folder(company) name */
    public IOTUpdateCommand(FactoryData factoryData) {
        pair = Pair.of(factoryData.getData(), factoryData.getResponder());
        dbms = factoryData.getDbms();
    }

    @Override
    public void run() {
        dbms.IOTUpdate(pair);
    }
}

class PingCommand implements Command {
    private final Responder responder;

    public PingCommand(FactoryData factoryData) {
        this.responder = factoryData.getResponder();
    }

    @Override
    public void run() {
        responder.respond("pong");
    }
}