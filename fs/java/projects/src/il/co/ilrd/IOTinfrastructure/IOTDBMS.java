package il.co.ilrd.IOTinfrastructure;

import il.co.ilrd.hashmap.Pair;

public interface IOTDBMS {

    void companyAdd(Pair<String, Responder> data);

    void productAdd(Pair<String, Responder> data);

    void IOTAdd(Pair<String, Responder> data);

    void IOTUpdate(Pair<String, Responder> data);

}
