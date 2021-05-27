package Client;

import Client.View.utils.AvatarUtil;
import Common.entity.Group;
import Common.entity.Request;
import Common.entity.User;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

public class ClientUtil {
    
    public static Request sendRequestAndReceive(Request request) throws IOException {
        Request returnRequest = null;
        ObjectOutputStream oos = ClientCache.getOos();
        try {
            oos.writeObject(request);// 发送请求
            oos.flush();
            System.out.println("Client send request :" + request.getRequestType());
            returnRequest = (Request) ClientCache.getOis().readObject();
            System.out.println("Client received request :" + returnRequest.getRequestType());
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        return returnRequest;
    }
    
    /**
     * 发送请求对象,不主动接收响应
     */
    public static void sendRequest(Request request) throws IOException {
        ObjectOutputStream oos = ClientCache.getOos();
        oos.writeObject(request); // 发送请求
        oos.flush();
        System.out.println("Client send request :" + request.getRequestType());
    }
    
    public static void initClientDate(Request request) {
        ClientCache.currentUser = (User) request.getAttribute("user");
        ClientCache.friendUserList = (ArrayList<User>) request.getAttribute("friend_list");
        ClientCache.groupList = (ArrayList<Group>) request.getAttribute("group_list");
        AvatarUtil.saveUserAvatar(ClientCache.currentUser.getAvatar(), ClientCache.currentUser.getUid());
        
    }
    
}