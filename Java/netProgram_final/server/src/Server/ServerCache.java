package Server;

import Common.entity.Group;
import Common.entity.User;
import Common.util.SocketIO;

import java.net.ServerSocket;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Map;

/**
 * 这是一个服务器端缓存类
 *
 * @author Java_Team
 * @version 1.5
 */

public class ServerCache {
    /**
     * 服务器套接字
     */
    public static ServerSocket serverSocket;
    /**
     * 在线用户的IO MAP
     */
    public static Map<Long, SocketIO> onlineUserIOCacheMap = new Hashtable<>();
    /**
     * 在线用户Map
     */
    public static Map<Long, User> onlineUsersMap = new Hashtable<>();
    /**
     * 已获取的group
     */
    public static Map<Long, Group> groupMapCache = new HashMap<>();
}
