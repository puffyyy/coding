package Server;

import Server.Controller.RequestProcessor;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerSetup {
    private static final int PORT = 5500;
    
    public static void main(String[] args) {
        try {
            ServerCache.serverSocket = new ServerSocket(PORT);
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
}
