package Common.entity;

import java.io.Serializable;
import java.util.ArrayList;

/**
 * 这是一个类 代表群聊实体
 *
 * @author Java_Team
 * @version 1.5
 */
public class Group implements Serializable {
    private static final long serialVersionUID = 5453963650970700287L;
    public Long gid;
    public String name;
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
    
    public Group(String name, ArrayList<User> users) {
        this.name = name;
        this.users = users;
        messages = new ArrayList<>();
    }
    
    public Group() {
    
    }
    
    public Group(Group g) {
        this.gid = g.gid;
        this.name = g.name;
        this.users = g.users;
        this.messages = g.messages;
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
