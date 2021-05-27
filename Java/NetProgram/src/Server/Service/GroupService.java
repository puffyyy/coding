package Server.Service;

import Common.entity.Group;
import Server.DAO.GroupDao;
import Server.DAO.UserDao;

import java.util.ArrayList;

public class GroupService {
    public static ArrayList<Group> selectGroupByUid(Long uid) {
        return UserDao.initialGroup(uid);
    }
    
    public static Group selectByGid(Long gid) {
        return GroupDao.selectGroupByGid(gid);
    }
    
}
