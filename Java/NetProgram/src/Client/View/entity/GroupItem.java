package Client.View.entity;

import Common.entity.Group;
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
        if (g.getMessages().size() > 0) {
            lastText = g.getMessages().get(0).getContent();
            timestamp = g.getMessages().get(0).getSendTime().getTime();
        } else {
            lastText = "";
            timestamp = -1;
        }
        unreadCount = 0;
        type = "text";
    }
    
    public GroupItem(Long roomId, String title, String lastText, int unreadCount, long timestamp, String type) {
        this.roomId = roomId;
        this.title = title;
        this.lastText = lastText;
        this.unreadCount = unreadCount;
        this.timestamp = timestamp;
        this.type = type;
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
