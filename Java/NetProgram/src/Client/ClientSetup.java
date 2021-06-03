package Client;

import Client.View.LoginFrame;

import javax.swing.*;
import java.io.*;
import java.net.Socket;

public class ClientSetup {
    public static void connectToServer() {
        try {
            ClientCache.clientSocket = new Socket(ClientCache.IP, ClientCache.PORT);
            InputStream is = ClientCache.clientSocket.getInputStream();
            OutputStream os = ClientCache.clientSocket.getOutputStream();
            ClientCache.ois = new ObjectInputStream(is);
            ClientCache.oos = new ObjectOutputStream(os); 
            ClientCache.isConnected = true;
        } catch (IOException e) {
            e.printStackTrace();
            ClientCache.isConnected = false;
            JOptionPane.showMessageDialog(new JFrame(),
                    "连接服务器失败,请检查!", "服务器未连接", JOptionPane.ERROR_MESSAGE);
        }
    }
    
    public static void main(String[] args) {
        new Thread() {
            @Override
            public void run() {
                super.run();
                connectToServer();
            }
        }.start();
        new LoginFrame();
    }
}
