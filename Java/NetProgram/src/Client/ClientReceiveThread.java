package Client;

import Common.entity.Request;
import Common.entity.RequestType;

import java.io.IOException;
import java.io.ObjectInputStream;

import static Common.entity.RequestType.*;

public class ClientReceiveThread extends Thread {
    
    @Override
    public void run() {
        while (true) {
            ObjectInputStream ois = ClientCache.ois;
            //从请求输入流中读取到客户端提交的请求对象
            Request request = null;
            try {
                request = (Request) ois.readObject();
                RequestType requestType = request.getRequestType();   //获取请求中的动作
                System.out.println("Request from Server:" + request.getRequestType());
                if (requestType == REGISTER) {      //用户注册
                    register(request);
                }else if (requestType == LOGOUT) {       //请求断开连接
                    logout(request);
                    break;
                } else if (requestType == SEND_MESSAGE) {       //聊天
                    receiveMessage(request);
                }
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
            
        }
    }
    
    private void receiveMessage(Request request) {
    }
    
    private void logout(Request request) {
        
    }
    private void register(Request request) {
    }
    
}
