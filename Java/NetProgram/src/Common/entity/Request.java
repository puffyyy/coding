package Common.entity;

import java.io.Serializable;
import java.util.HashMap;

/**
 * 这是一个类 代表客户端请求实体
 *
 * @author Java_Team
 * @version 1.5
 */
public class Request implements Serializable {
    private static final long serialVersionUID = -4105920881726156018L;
    private final RequestType requestType;
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
}
