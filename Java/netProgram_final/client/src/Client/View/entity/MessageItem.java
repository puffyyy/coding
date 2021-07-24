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

    /**
     * 消息实体项的构造方法之一
     * @param m 一个消息实体
     * @param g 会话群组
     */
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

    /**
     * 消息实体项的构造方法之一
     * @param currentUser 当前信息的来源用户
     * @param str 消息内容文本，将其加工带上时间信息
     */
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
