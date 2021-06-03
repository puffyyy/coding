package Client.View.entity;

import Client.View.utils.TimeUtil;
import Common.entity.Group;
import Common.entity.Message;
import Common.entity.User;

import java.util.ArrayList;
import java.util.Date;

public class MessageItem extends Message {
    User from;
    String content_time;
    
    public MessageItem(Message m, Group g) {
        super();
        content_time = m.getContent() + "[" + TimeUtil.diff(m.getSendTime().getTime()) + "]";
        this.setGroupId(m.getGroupId());
        this.setSendTime(m.getSendTime());
        ArrayList<User> arr = g.users;
        for (User u : arr) {
            if (u.getUid() == m.getFromUserId()) {
                from = u;
                break;
            }
        }
    }
    
    public MessageItem(User currentUser, String str) {
        from = currentUser;
        content_time = str + "[" + TimeUtil.diff(new Date().getTime()) + "]";
    }
    
    public String getContent_time() {
        return content_time;
    }
    
    public User getFrom() {
        return from;
    }
}
