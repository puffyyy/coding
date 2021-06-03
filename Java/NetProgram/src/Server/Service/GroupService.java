package Server.Service;

import Common.entity.Group;
import Common.entity.User;
import Server.DAO.GroupDao;
import Server.ServerCache;

import java.util.ArrayList;

/**
 * 这是一个类 提供群聊处理的方法
 *
 * @author Java_Team
 * @version 1.5
 */

public class GroupService {
    /**
     * 查找指定群组
     *
     * @param gid 群id
     * @return group 群对象
     */
    public static Group selectByGid(Long gid) {
        Group g = GroupDao.selectGroupByGid(gid);
        ServerCache.groupMapCache.put(gid, g);
        return g;
    }
    
    /**
     * 查看群成员
     *
     * @param gid 群id
     * @return users 群成员列表
     */
    public static ArrayList<User> selectGroupMemberByGid(Long gid) {
        return GroupDao.groupMembers(gid);
    }
    
    /**
     * 创建群聊
     *
     * @param name  群名称
     * @param users 群成员列表
     * @return gid 群id
     */
    public static Long createGroup(String name, ArrayList<Long> users) {
        return GroupDao.createGroup(users, name);
    }
}
