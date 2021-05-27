package Server.Service;

import Common.entity.User;

import java.util.ArrayList;

import static Server.DAO.FriendDao.*;
import static Server.Service.UserService.addAvatarList;

public class FriendService {
    public ArrayList<Long> getFriendIdList(Long uid) {
        return selectFriendsById(uid);
    }
    
    public ArrayList<User> getFriendListByUid(Long uid) {
        return addAvatarList(friendList(uid));
    }
    
    public void addFriend(Long uid1, Long uid2) {
        insertFriend(uid1, uid2);
    }
    
    public void removeFriend(Long uid1, Long uid2) {
        deleteFriend(uid1, uid2);
    }
}
