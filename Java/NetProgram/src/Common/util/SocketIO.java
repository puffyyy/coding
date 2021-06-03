package Common.util;

import java.io.*;
import java.net.Socket;

/**
 * 这是一个类 套接字IO
 *
 * @author Java_Team
 * @version 1.5
 */

public class SocketIO {
    private final ObjectInputStream ois; // 对象输入流
    private final ObjectOutputStream oos; // 对象输出流
    
    public SocketIO(ObjectInputStream ois, ObjectOutputStream oos) {
        this.ois = ois;
        this.oos = oos;
    }
    
    public ObjectOutputStream getOos() {
        return oos;
    }
    
    public ObjectInputStream getOis() {
        return ois;
    }
    
    public static void close(InputStream is) {
        if (null != is) {
            try {
                is.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    
    public static void close(OutputStream os) {
        if (null != os) {
            try {
                os.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    
    public static void close(InputStream is, OutputStream os) {
        close(is);
        close(os);
    }
    
    public static void close(Socket socket) {
        try {
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
