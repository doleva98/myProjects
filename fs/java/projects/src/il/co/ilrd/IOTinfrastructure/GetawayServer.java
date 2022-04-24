package il.co.ilrd.IOTinfrastructure;

import il.co.ilrd.factory.Factory;

class GatewayServer {
    private ConnectionServer connectionServer = null;
    private OperationManager operationManager = null;
    private final Factory<Command, FactoryData, String> commandFactory = new Factory<>();
    private IOTDBMS dbms;

    public GatewayServer(int port, String url, String username, String password) {
        commandFactory.add("CompanyRegisterCommand", CompanyRegisterCommand::new);
        commandFactory.add("ProductRegisterCommand", ProductRegisterCommand::new);
        commandFactory.add("IOTRegisterCommand", IOTRegisterCommand::new);
        commandFactory.add("IOTUpdateCommand", IOTUpdateCommand::new);
        commandFactory.add("ping", PingCommand::new);
        dbms = new MySQLDBMS(url, username, password);
        operationManager = new OperationManager(dbms, commandFactory);
        connectionServer = new ConnectionServer(port);
    }

    public void start() {
        connectionServer.start(operationManager);
    }

    public void stop() {
        operationManager.stop();
        connectionServer.stop();
    }

}
