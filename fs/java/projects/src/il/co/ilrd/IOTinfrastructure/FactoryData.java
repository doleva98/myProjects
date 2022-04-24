package il.co.ilrd.IOTinfrastructure;

public class FactoryData {
    private String data = null;
    private Responder responder = null;
    private IOTDBMS dbms = null;

    public FactoryData(String data, Responder responder, IOTDBMS dbms) {
        this.data = data;
        this.responder = responder;
        this.dbms = dbms;
    }

    public String getData() {
        return this.data;
    }

    public Responder getResponder() {
        return this.responder;
    }

    public IOTDBMS getDbms() {
        return this.dbms;
    }

}
