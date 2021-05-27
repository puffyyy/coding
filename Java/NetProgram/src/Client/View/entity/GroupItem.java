package Client.View.entity;

import Client.ClientCache;
import Common.entity.Group;
import Common.entity.Message;
import Common.entity.User;

import java.util.ArrayList;

public class GroupItem implements Comparable<GroupItem> {
    private Long roomId;
    private ArrayList<User> groupMember;
    private String title;
    private String lastText;
    private int unreadCount;
    private long timestamp;
    private String type;
    
    public GroupItem(Group g) {
        roomId = g.getGid();
        groupMember = g.getUsers();
        title = g.getName();
        unreadCount = 0;
        if (g.getMessages().size() > 0) {
            Message m = g.getMessages().get(0);
            if (groupMember.size() == 2) {
                type = "channel";
                lastText = m.getContent();
            } else {
                type = "group";
                if (m.getFromUserId() == ClientCache.currentUser.getUid()) {
                    lastText = m.getContent();
                } else {
                    Long from_uid = m.getFromUserId();
                    String from_name = "user";
                    from_name = g.users.stream().filter(u -> u.getUid() == from_uid).findFirst().map(User::getUsername).orElse(from_name);
                    lastText = from_name + ":" + m.getContent();
                }
            }
            timestamp = m.getSendTime().getTime();
        } else {
            lastText = "";
            timestamp = -1;
        }
    }
    
    public Long getRoomId() {
        return roomId;
    }
    
    public void setRoomId(Long roomId) {
        this.roomId = roomId;
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
    
    public ArrayList<User> getGroupMember() {
        return groupMember;
    }
    
    public void setGroupMember(ArrayList<User> groupMember) {
        this.groupMember = groupMember;
    }
    
    @Override
    public String toString() {
        return "RoomItem{" +
                "roomId='" + roomId + '\'' +
                ", title='" + title + '\'' +
                ", lastMessage='" + lastText + '\'' +
                ", unreadCount=" + unreadCount +
                ", timestamp='" + timestamp + '\'' +
                '}';
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
