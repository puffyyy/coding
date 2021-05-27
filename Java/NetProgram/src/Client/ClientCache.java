package Client;

import Common.entity.Group;
import Common.entity.User;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;

public class ClientCache {
    public static boolean isConnected = false;
    public static User currentUser;
    public static ArrayList<User> friendUserList;
    public static ArrayList<Group> groupList;
    public static Socket clientSocket;//当前客户端连接到服务器的套节字
    public static ObjectInputStream ois; // 对象输入流
    public static ObjectOutputStream oos; // 对象输出流
    public static String IP;//本客户端的IP地址
    //todo map<gid,list<message> >
    public static int PORT;
    
    static {
        IP = "localhost";
        PORT = 5500;
    }
    
    public static ObjectInputStream getOis() {
        return ois;
    }
    
    public static ObjectOutputStream getOos() {
        return oos;
    }
    
    public static boolean isIsConnected() {
        return isConnected;
    }
    
    public static void setIsConnected(boolean isConnected) {
        ClientCache.isConnected = isConnected;
    }
}
