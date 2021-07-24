package Client;

import Client.View.entity.GroupItem;
import Client.View.entity.NoticeItem;
import Client.View.utils.AvatarUtil;
import Client.View.utils.ImageUtil;
import Common.entity.Group;
import Common.entity.Notice;
import Common.entity.Request;
import Common.entity.User;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class ClientUtil {
    /**
     * 发送请求对象,主动接收响应
     */
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
            ClientCache.isConnected = false;
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
        if (ClientCache.currentUser.getPicture() == null)
            ClientCache.currentUser.setAvatar(ImageUtil.toBufferedImage(AvatarUtil.createOrLoadUserAvatar(ClientCache.currentUser)));
        ClientCache.friendUserList = (ArrayList<User>) request.getAttribute("friend_list");
        ArrayList<Group> groups = (ArrayList<Group>) request.getAttribute("group_list");
        ArrayList<GroupItem> groupItems = new ArrayList<>();
        HashMap<Long, GroupItem> groupItemHashMap = new HashMap<>();
        for (Group g : groups) {
            GroupItem gi = new GroupItem(g);
            groupItems.add(gi);
            if (gi.getType().equals("channel")) {
                for (User contractor : gi.getUsers()) {
                    if (contractor.getUid() != ClientCache.currentUser.getUid()) {
                        groupItemHashMap.put(contractor.getUid(), gi);
                        break;
                    }
                    AvatarUtil.saveUserAvatar(ImageUtil.toBufferedImage(AvatarUtil.createOrLoadUserAvatar(contractor)), contractor.getUid());
                }
            }
        }
        ClientCache.contractorGroupMap = groupItemHashMap;
        ClientCache.groupList = groupItems;
        AvatarUtil.saveUserAvatar(ClientCache.currentUser.getAvatar(), ClientCache.currentUser.getUid());
        ClientCache.friendUserList.forEach(u -> AvatarUtil.saveUserAvatar(ImageUtil.toBufferedImage(AvatarUtil.createOrLoadUserAvatar(u)), u.getUid()));
        
        HashMap<Notice, User> noticeUserHashMap = (HashMap<Notice, User>) request.getAttribute("notice_map");
        Iterator<Map.Entry<Notice, User>> iter = noticeUserHashMap.entrySet().iterator();
        ArrayList<NoticeItem> noticeItems = new ArrayList<>();
        while (iter.hasNext()) {
            Map.Entry<Notice, User> entry = iter.next();
            Notice notice = entry.getKey();
            noticeItems.add(new NoticeItem(entry.getValue(), notice.getGetId(), notice.getTime(), notice.getContent(), notice.getType()));
        }
        ClientCache.noticeList = noticeItems;
    }
    
}