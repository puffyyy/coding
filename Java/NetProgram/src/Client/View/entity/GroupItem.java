package Client.View.entity;

import Client.ClientCache;
import Common.entity.Group;
import Common.entity.Message;
import Common.entity.User;

public class GroupItem extends Group implements Comparable<GroupItem> {
    private static final long serialVersionUID = 6208515677581990400L;
    private String title;
    private String lastText;
    private int unreadCount;
    private long timestamp;
    private String type;
    private User toUser;
    
    public GroupItem(Group g) {
        super(g);
        title = g.getName();
        unreadCount = 0;
        if (this.getMessages().size() > 0) {
            Message m = this.getMessages().get(getMessages().size() - 1);
            if (this.users.size() == 2) {
                type = "channel";
                for (User u : users) {
                    if (u.getUid() != ClientCache.currentUser.getUid()) {
                        toUser = u;
                        title = u.getUsername();
                        break;
                    }
                }
                lastText = m.getContent();
            } else {
                type = "group";
                if (m.getFromUserId() == ClientCache.currentUser.getUid()) {
                    lastText = m.getContent();
                } else {
                    Long from_uid = m.getFromUserId();
                    String from_name = "User";
                    from_name = this.users.stream().filter(u -> u.getUid() == from_uid).findFirst().map(User::getUsername).orElse(from_name);
                    lastText = from_name + ":" + m.getContent();
                }
            }
            timestamp = m.getSendTime().getTime();
        } else {
            if (this.users.size() == 2) {
                type = "channel";
                for (User u : users) {
                    if (u.getUid() != ClientCache.currentUser.getUid()) {
                        toUser = u;
                        title = u.getUsername();
                        break;
                    }
                }
            } else
                type = "group";
            lastText = "";
            timestamp = -1;
        }
    }
    
    public String getTitle() {
        return title;
    }
    
    public void setTitle(String title) {
        this.title = title;
    }
    
    public String getLastText() {
        return lastText;
    }
    
    public void setLastText(String lastText) {
        this.lastText = lastText;
    }
    
    public int getUnreadCount() {
        return unreadCount;
    }
    
    public void setUnreadCount(int unreadCount) {
        this.unreadCount = unreadCount;
    }
    
    public long getTimestamp() {
        return timestamp;
    }
    
    public void setTimestamp(long timestamp) {
        this.timestamp = timestamp;
    }
    
    public User searchUserById(Long id) {
        for (User u : users) {
            if (u.getUid() == id)
                return u;
        }
        return null;
    }
    
    @Override
    public String toString() {
        return "RoomItem{" +
                "roomId='" + gid + '\'' +
                ", title='" + title + '\'' +
                ", lastMessage='" + lastText + '\'' +
                ", unreadCount=" + unreadCount +
                ", timestamp='" + timestamp + '\'' +
                '}';
    }
    
    public void updateLastMessage(Message m) {
        lastText = m.getContent();
        timestamp = m.getSendTime().getTime();
        if (type.equals("channel")) {
            lastText = m.getContent();
        } else {
            if (m.getFromUserId() == ClientCache.currentUser.getUid()) {
                lastText = m.getContent();
            } else {
                Long from_uid = m.getFromUserId();
                String from_name = "User";
                from_name = this.users.stream().filter(u -> u.getUid() == from_uid).findFirst().map(User::getUsername).orElse(from_name);
                lastText = from_name + ":" + m.getContent();
            }
        }
    }
    
    public String getType() {
        return type;
    }
    
    public void setType(String type) {
        this.type = type;
    }
    
    public int compareTo(GroupItem o) {
        long ret = o.getTimestamp() - this.getTimestamp();
        return ret > 0 ? 1 : -1;
    }
    
}
