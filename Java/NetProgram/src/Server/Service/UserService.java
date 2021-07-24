package Server.Service;

import Common.entity.Group;
import Common.entity.User;
import Server.DAO.UserDao;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

/**
 * 这是一个类 提供用户事务的处理方法
 *
 * @author Java_Team
 * @version 1.5
 */

public class UserService {
    /**
     * 用户注册
     *
     * @param username  用户昵称
     * @param password  密码
     * @param sex       性别
     * @param path      头像
     * @param phone_num 电话号
     * @return uid 用户id
     */
    public static Long registerNewUser(String username, String password, char sex, String path, String phone_num) {
        Object[] arr = new Object[]{username, password, String.valueOf(sex), path, phone_num};
        return UserDao.insertUser(arr);
    }
    
    /**
     * 关键字查找用户
     *
     * @param key 关键字
     * @return users 用户列表
     */
    public static ArrayList<User> searchUserByKeywords(String key) {
        return addAvatarList(UserDao.selectUserByKeyWords(key));
    }
    
    /**
     * id查询用户
     *
     * @param id 用户id
     * @return user 用户实体
     */
    public static User selectUserById(long id) {
        User u = UserDao.selectUserById(id);
        return addAvatar(u);
    }
    
    /**
     * 为指定用户添加头像
     *
     * @param u 用户实体
     * @return user 修改后的用户实体
     */
    public static User addAvatar(User u) {
        if (u != null) {
            String path = u.getAvatarPath();
            try {
                BufferedImage image = ImageIO.read(new File(path));
                u.setAvatar(image);
            } catch (IOException e) {
                System.out.println(u.getUid() + "default avatar");
                return u;
            }
        }
        return u;
    }
    
    /**
     * 为一组用户添加头像
     *
     * @param list 用户列表
     * @return users 修改后的用户列表
     */
    public static ArrayList<User> addAvatarList(ArrayList<User> list) {
        if (list != null) {
            for (User u : list) {
                addAvatar(u);
            }
        }
        return list;
    }
    
    /**
     * 修改个人信息
     *
     * @param uid           用户id
     * @param modifyContent 修改内容
     * @param type          修改类别
     * @return bool 是否成功
     */
    public static boolean modifyPersonalInformation(Long uid, String modifyContent, String type) {
        switch (type) {
            case "username":
                return UserDao.modifyUsername(uid, modifyContent);
            case "password":
                return UserDao.modifyPassword(uid, modifyContent);
            case "avatar_path":
                return UserDao.modifyAvatar(uid, modifyContent);
            case "phone_num":
                return UserDao.modifyPhone(uid, modifyContent);
            default:
                return false;
        }
    }
    
    public static void delectUser(Long uid) {
        UserDao.deleteUserById(uid);
    }
    
    /**
     * 初始化用户登录后的主页面
     *
     * @param uid 用户id
     * @return groups 会话窗口
     */
    public static ArrayList<Group> initGroupList(Long uid) {
        ArrayList<Group> arr =  UserDao.initialGroup(uid);
        if (arr != null) {
            for (Group g : arr){
                addAvatarList(g.getUsers());
            }
        }
        return arr;
    }
}

