package Common.entity;

import java.io.Serializable;
import java.util.HashMap;

public class Request implements Serializable {
    private static final long serialVersionUID = -4105920881726156018L;
    private final RequestType requestType;
//    private boolean requestNeedRespond = true;
    /**
     * map
     * <p>
     * user : User
     * message : Message
     * <p>
     * //response_state : ok/bad
     */
    private final HashMap<String, Object> dataMap;
    
    public Request(RequestType requestType) {
        this.requestType = requestType;
        this.dataMap = new HashMap<>();
    }
    
    public RequestType getRequestType() {
        return requestType;
    }
    
    public HashMap<String, Object> getDataMap() {
        return dataMap;
    }
    
    public void setAttribute(String name, Object value) {
        this.dataMap.put(name, value);
    }
    
    public Object getAttribute(String name) {
        return this.dataMap.get(name);
    }
    
//    public boolean isRequestNeedRespond() {
//        return requestNeedRespond;
//    }
//
//    public void setRequestNeedRespond(boolean requestNeedRespond) {
//        this.requestNeedRespond = requestNeedRespond;
//    }
}
