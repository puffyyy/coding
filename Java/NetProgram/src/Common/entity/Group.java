package Common.entity;

import java.io.Serializable;
import java.util.ArrayList;

public class Group implements Serializable {
    private static final long serialVersionUID = 5453963650970700287L;
    private Long gid;
    private String name;
    private String avatarPath;
    public ArrayList<User> users;
    public ArrayList<Message> messages;
    
    public Group(Long gid, String name, String avatarPath, ArrayList<User> users) {
        this.gid = gid;
        this.name = name;
        this.avatarPath = avatarPath;
        this.users = users;
    }
    
    public Group(Long gid, String name, String avatarPath, ArrayList<User> users, ArrayList<Message> messages) {
        this.gid = gid;
        this.name = name;
        this.avatarPath = avatarPath;
        this.users = users;
        this.messages = messages;
    }
    
    public Group() {
    
    }
    
    @Override
    public String toString() {
        return "Group{" +
                "gid=" + gid +
                ", name='" + name + '\'' +
                ", avatarPath='" + avatarPath + '\'' +
                ", users=" + users +
                ", messages=" + messages +
                '}';
    }
    
    public ArrayList<User> getUsers() {
        return users;
    }
    
    public void setUsers(ArrayList<User> users) {
        this.users = users;
    }
    
    public ArrayList<Message> getMessages() {
        return messages;
    }
    
    public void setMessages(ArrayList<Message> messages) {
        this.messages = messages;
    }
    
    public Long getGid() {
        return gid;
    }
    
    public void setGid(Long gid) {
        this.gid = gid;
    }
    
    public String getName() {
        return name;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public String getAvatarPath() {
        return avatarPath;
    }
    
    public void setAvatarPath(String avatarPath) {
        this.avatarPath = avatarPath;
    }
}
