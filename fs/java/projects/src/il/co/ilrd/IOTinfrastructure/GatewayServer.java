package il.co.ilrd.IOTinfrastructure;

import il.co.ilrd.factory.Factory;

class GatewayServer {
    private final ConnectionServer connectionServer;
    private final OperationManager operationManager;
    private final Factory<Command, FactoryData, String> commandFactory = new Factory<>();
    private final IOTDBMS dbms;

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

    public static void main(String[] args) {
        new GatewayServer(1234, "jdbc:mysql://localhost:3306/", "root", "").start();

    }
}
