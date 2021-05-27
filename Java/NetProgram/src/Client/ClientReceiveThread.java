package Client;

import Client.View.LeftFrame.AddFriendDialog;
import Client.View.LeftFrame.ListPanel;
import Common.entity.Group;
import Common.entity.Request;
import Common.entity.RequestType;
import Common.entity.User;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;

public class ClientReceiveThread extends Thread {
    
    @Override
    public void run() {
        ObjectInputStream ois = ClientCache.ois;
        boolean flag = true;
        while (flag) {
            //从请求输入流中读取到客户端提交的请求对象
            Request request = null;
            try {
                request = (Request) ois.readObject();
                RequestType requestType = request.getRequestType();   //获取请求中的动作
                System.out.println("Request from Server:" + request.getRequestType());
                switch (requestType) {
                    case REGISTER:       //用户注册
                        register(request);
                        break;
                    case LOGOUT:        //请求断开连接
                        logout(request);
                        flag = false;
                        break;
                    case SEND_MESSAGE:        //聊天
                        receiveMessage(request);
                        break;
                    case ADD_FRIEND:
                        addFriend(request);
                        break;
                    case JOIN_GROUP:    //收到加入群聊
                        joinGroup(request);
                        break;
                }
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
            
        }
    }
    
    private void joinGroup(Request request) {
        Group g = (Group) request.getAttribute("group");
        ClientCache.groupList.add(g);
        //todo add popup
        ListPanel.getContext().refreshRooms();
        //todo room list sequence
    }
    
    private void addFriend(Request request) {
        String method = (String) request.getAttribute("method");
        switch (method) {
            case "user_list":
                ArrayList<User> list = (ArrayList<User>) request.getAttribute("user_list");
                AddFriendDialog.getContent().updateListModel(list);
                if(list.size()==0)AddFriendDialog.getContent().showErrorMessage();
                break;
            case "add_friend_from":
                //todo notice to Mainframe update contractor list panel
                break;
            case "add_user_to":
                //todo notice to Mainframe update contractor list panel
                break;
        }
    }
    
    private void receiveMessage(Request request) {
    }
    
    private void logout(Request request) {
        
    }
    
    private void register(Request request) {
    }
    
}
