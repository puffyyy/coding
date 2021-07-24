package Client;

import Client.View.entity.GroupItem;
import Client.View.entity.NoticeItem;
import Common.entity.User;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;

public class

ClientCache {
    public static boolean isConnected = false;
    public static Thread receiveThread;
    public static User currentUser;
    public static ArrayList<User> friendUserList;
    public static ArrayList<GroupItem> groupList;
    public static ArrayList<NoticeItem> noticeList;
    public static HashMap<Long, GroupItem> contractorGroupMap;
    public static Socket clientSocket;//当前客户端连接到服务器的套节字
    public static ObjectInputStream ois; // 对象输入流
    public static ObjectOutputStream oos; // 对象输出流
    public static String IP;//服务器端的IP地址
    public static int PORT;
    
    static {
        IP = "localhost";//10.128.77.116
        PORT = 5500;
    }
    
    public static ObjectInputStream getOis() {
        return ois;
    }
    
    public static ObjectOutputStream getOos() {
        return oos;
    }
}
