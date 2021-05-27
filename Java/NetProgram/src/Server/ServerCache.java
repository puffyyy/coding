package Server;

import Common.entity.User;
import Common.util.SocketIO;

import java.net.ServerSocket;
import java.util.Hashtable;
import java.util.Map;

public class ServerCache {
    // 服务器端套接字
    public static ServerSocket serverSocket;
    //在线用户的IO Map
    public static Map<Long, SocketIO> onlineUserIOCacheMap=new Hashtable<>();
    //在线用户Map
    public static Map<Long, User> onlineUsersMap=new Hashtable<>();
}
