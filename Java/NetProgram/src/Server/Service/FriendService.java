package Server.Service;

import Common.entity.User;

import java.util.ArrayList;

import static Server.DAO.FriendDao.*;
import static Server.Service.UserService.addAvatarList;

/**
 * 这是一个类 提供处理好友事务的方法
 *
 * @author Java_Team
 * @version 1.5
 */

public class FriendService {
    /**
     * 获取好友列表
     *
     * @param uid 用户id
     * @return friends 好友id列表
     * @deprecated
     */
    public static ArrayList<Long> getFriendIdList(Long uid) {
        return selectFriendsById(uid);
    }
    
    /**
     * 获取好友列表
     *
     * @param uid 用户id
     * @return friends 好友列表
     */
    public static ArrayList<User> getFriendListByUid(Long uid) {
        return addAvatarList(friendList(uid));
    }
    
    /**
     * 添加好友
     *
     * @param uid1 用户1
     * @param uid2 用户2
     * @return gid 群聊id
     */
    public static Long addFriend(Long uid1, Long uid2) {
        return insertFriend(uid1, uid2);
    }
    
    /**
     * 解除好友关系
     *
     * @param uid1 用户1
     * @param uid2 用户2
     */
    public static void removeFriend(Long uid1, Long uid2) {
        deleteFriend(uid1, uid2);
    }
}
