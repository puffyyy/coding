package Common.entity;

import java.awt.image.BufferedImage;
import java.io.Serializable;

public class User implements Serializable {
    
    private static final long serialVersionUID = -2597817861630142303L;
    private Long uid;
    private String password;
    private String username;
    private char sex;
    private String phoneNum;
    private String avatarPath;
    private Picture avatar;
    
    public User(Long uid,  String username, String password,char sex, String phoneNum, String avatarPath) {
        this.uid = uid;
        this.password = password;
        this.username = username;
        this.sex = sex;
        this.phoneNum = phoneNum;
        this.avatarPath = avatarPath;
    }
    
    /*
        login
     */
    public User(long uid, String password) {
        this.uid = uid;
        this.password = password;
    }
    
    /*
        register
    */
    public User(String username, String password, char sex) {
        this.username = username;
        this.password = password;
        this.sex = sex;
    }
    
    /*
        db return
     */
    public User(long uid, String password, String nickname, char sex) {
        this.uid = uid;
        this.password = password;
        this.username = nickname;
        this.sex = sex;
    }
    
    public long getUid() {
        return uid;
    }
    
    public void setUid(long uid) {
        this.uid = uid;
    }
    
    public String getPassword() {
        return password;
    }
    
    public void setPassword(String password) {
        this.password = password;
    }
    
    public String getUsername() {
        return username;
    }
    
    public void setUsername(String username) {
        this.username = username;
    }
    
    public char getSex() {
        return sex;
    }
    
    public void setSex(char sex) {
        this.sex = sex;
    }
    
    public String getPhoneNum() {
        return phoneNum;
    }
    
    public void setPhoneNum(String phoneNum) {
        this.phoneNum = phoneNum;
    }
    
    public String getAvatarPath() {
        return avatarPath;
    }
    
    public void setAvatarPath(String avatarPath) {
        this.avatarPath = avatarPath;
    }
    
    public BufferedImage getAvatar() {
        return avatar.getImg();
    }
    
    public void setAvatar(BufferedImage img) {
        if (this.avatar == null) {
            this.avatar = new Picture();
        }
        this.avatar.setImg(img);
    }
    
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        
        User user = (User) o;
        
        if (uid != user.uid) return false;
        if (sex != user.sex) return false;
        if (!password.equals(user.password)) return false;
        return username.equals(user.username);
    }
    
    @Override
    public int hashCode() {
        int result = (int) (uid ^ (uid >>> 32));
        result = 31 * result + password.hashCode();
        result = 31 * result + username.hashCode();
        result = 31 * result + (int) sex;
        return result;
    }
    
    @Override
    public String toString() {
        return "User{" +
                "uid=" + uid +
                ", password='" + password + '\'' +
                ", username='" + username + '\'' +
                ", sex=" + sex +
                ", phoneNum='" + phoneNum + '\'' +
                ", avatarPath='" + avatarPath + '\'' +
                '}';
    }
}
