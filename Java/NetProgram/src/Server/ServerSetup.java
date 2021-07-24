package Server;

import Server.DAO.DBUtil;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Properties;

/**
 * 这是一个服务器启动的方法类
 *
 * @author Java_Team
 * @version 1.5
 */

public class ServerSetup {
    private static int PORT;
    
    public static void main(String[] args) {
        try {
            initServerProperties();
            ServerCache.serverSocket = new ServerSocket(PORT);
            File file = new File("./cache");
//            System.out.println(file.getAbsolutePath());
            if (!file.exists()) {
                file.mkdirs();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            while (true) {
                // 监听客户端的连接
                Socket socket = ServerCache.serverSocket.accept();
                System.out.println("Client accept "
                        + socket.getInetAddress().getHostAddress()
                        + ":" + socket.getPort());
                
                //针对每个客户端启动一个线程，在线程中调用请求处理器来处理每个客户端的请求
                new Thread(new RequestProcessor(socket)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public static void initServerProperties() {
        Properties pro = new Properties();
        InputStream in = ServerSetup.class.getClassLoader().getResourceAsStream("server.properties");
        try {
            pro.load(in);
            ServerSetup.PORT = Integer.parseInt(pro.getProperty("PORT"));
            DBUtil.db_name = pro.getProperty("DBNAME");
            DBUtil.db_pass = pro.getProperty("DBPASS");
            DBUtil.db_user = pro.getProperty("DBUSER");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
