package Client;

import Client.View.LeftFrame.AddFriendDialog;
import Client.View.LeftFrame.ListPanel;
import Client.View.MainFrame;
import Client.View.RightFrame.RightPanel;
import Client.View.entity.GroupItem;
import Client.View.entity.NoticeItem;
import Common.entity.*;

import javax.swing.*;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;
import java.util.Arrays;

public class ClientReceiveThread extends Thread {
    public volatile boolean exit = false;
    
    @Override
    public void run() {
        ObjectInputStream ois = ClientCache.ois;
        exit = false;
        while (!exit) {
            //从请求输入流中读取到客户端提交的请求对象
            Request request = null;
            try {
                request = (Request) ois.readObject();
                RequestType requestType = request.getRequestType();   //获取请求中的动作
                System.out.println("Request from Server:" + request.getRequestType());
                switch (requestType) {
                    case LOGOUT:        //请求断开连接
                        logout(request);
                        exit = true;
                        break;
                    case SEND_MESSAGE:        //聊天
                        receiveMessage(request);
                        break;
                    case ADD_FRIEND:        //添加好友
                        addFriend(request);
                        break;
                    case JOIN_GROUP:    //收到加入群聊
                        joinGroup(request);
                        break;
                }
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
                if (MainFrame.getContext().isDisplayable())
                    JOptionPane.showMessageDialog(MainFrame.getContext(), "服务器断开连接", "网络中断", JOptionPane.WARNING_MESSAGE);
                ClientCache.isConnected = false;
                exit = true;
            }
        }
    }
    
    private void joinGroup(Request request) {
        Group g = (Group) request.getAttribute("group");
        User u = (User) request.getAttribute("from");
        ClientCache.groupList.add(new GroupItem(g));
        String str = u.getUsername() + "邀请加入群聊" + g.getName();
        if (u.getUid() == ClientCache.currentUser.getUid())
            str = "创建群聊" + g.getName() + "成功";
        JOptionPane.showMessageDialog(MainFrame.getContext(), str, "创建群聊", JOptionPane.INFORMATION_MESSAGE);
        ListPanel.getContext().refreshRooms();
    }
    
    private void addFriend(Request request) {
        String method = (String) request.getAttribute("method");
        switch (method) {
            case "user_list":
                ArrayList<User> list = (ArrayList<User>) request.getAttribute("user_list");
                list.stream().filter(u -> u.getUid() == ClientCache.currentUser.getUid()).findFirst().ifPresent(list::remove);
                AddFriendDialog.getContent().updateListModel(list);
                if (list.size() == 0) AddFriendDialog.getContent().showErrorMessage();
                break;
            case "add_friend_from":
                Notice noc = (Notice) request.getAttribute("notice");
                User u = (User) request.getAttribute("from");
                NoticeItem noticeItem = new NoticeItem(u, noc.getGetId(), noc.getTime(), noc.getContent(), noc.getType());
                ClientCache.noticeList.add(noticeItem);
                break;
            case "add_friend_to":
                Notice notice = (Notice) request.getAttribute("notice");
                User user = (User) request.getAttribute("user");
                Long gid = (Long) request.getAttribute("group_id");
                User[] arr = new User[]{user, ClientCache.currentUser};
                Group group = new Group(gid, "", "", new ArrayList<>(Arrays.asList(arr)));
                group.messages = new ArrayList<>();
                ClientCache.friendUserList.add(user);
                GroupItem groupItem = new GroupItem(group);
                ClientCache.groupList.add(groupItem);
                ClientCache.contractorGroupMap.put(user.getUid(), groupItem);
                JOptionPane.showMessageDialog(MainFrame.getContext(), user.getUsername() + "的好友申请已通过", "好友添加成功", JOptionPane.INFORMATION_MESSAGE);
                ListPanel.getContext().refreshContracts();
                ListPanel.getContext().refreshRooms();
                break;
        }
    }
    
    private void receiveMessage(Request request) {
        Message message = (Message) request.getAttribute("message");
        Long gid = message.getGroupId();
        GroupItem groupItem = null;
        for (GroupItem gi : ClientCache.groupList) {
            if (gi.getGid().equals(gid)) {
                groupItem = gi;
            }
        }
        if (groupItem != null) {
            groupItem.messages.add(message);
            groupItem.updateLastMessage(message);
            ListPanel.getContext().refreshRooms();
            if (RightPanel.getContext().getRoom().equals(groupItem))
                RightPanel.getContext().setRoom(groupItem);
            
        }
    }
    
    private void logout(Request request) {
        String state = (String) request.getAttribute("state");
        JOptionPane.showMessageDialog(MainFrame.getContext(), state, "退出登录", JOptionPane.WARNING_MESSAGE);
        MainFrame.getContext().dispose();
        exit = true;
    }
    
}
