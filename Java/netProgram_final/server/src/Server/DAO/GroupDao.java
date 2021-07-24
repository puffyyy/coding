package Server.DAO;

import Common.entity.Group;
import Common.entity.Message;
import Common.entity.User;

import java.sql.*;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Date;

/**
 * 这是一个类 在数据库层面处理群聊事务
 *
 * @author Java_Team
 * @version 1.5
 */

public class GroupDao {
    /**
     * 按最新消息的时间对会话框进行排序
     *
     * @param groups 所在的所有聊天群组
     */
    public static void sortInMessageTime(ArrayList<Group> groups) {
        groups.sort(new Comparator<Group>() {
            public int compare(Group p, Group q) {
                if (p.messages.size() != 0 && q.messages.size() != 0)
                    return p.messages.get(0).getSendTime().compareTo(q.messages.get(0).getSendTime());
                return p.messages.size() == 0 ? -1 : 1;
            }
        });
    }
    
    /**
     * 通过群组id查找指定群组
     *
     * @param gid 群组id
     * @return Group 群组对象
     */
    public static Group selectGroupByGid(Long gid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        PreparedStatement statement1 = null;
        try {
            statement = con.prepareStatement("select g_name,g_avatar_path from `group` where gid=?");
            statement.setLong(1, gid);
            ResultSet set = statement.executeQuery();
            String name = null;
            String path = null;
            if (set.next()) {
                name = set.getString(1);
                path = set.getString(2);
            }
            statement1 = con.prepareStatement("select userid from user_in_group where group_id =?");
            statement1.setLong(1, gid);
            set = statement1.executeQuery();
            ArrayList<User> users = new ArrayList<User>();
            while (set.next()) {
                Long uid = set.getLong(1);
                User user = UserDao.selectUserById(uid);
                users.add(user);
            }
            ArrayList<Message> messages = new ArrayList<Message>();
            messages = RecentMessageRecordDao.groupMessage(gid);
            return new Group(gid, name, path, users, messages);
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 获取群成员
     *
     * @param gid 群组id
     * @return ArrayList<user> 用户列表
     */
    public static ArrayList<User> groupMembers(Long gid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        ArrayList<User> users = new ArrayList<>();
        try {
            statement = con.prepareStatement("select userid from user_in_group where group_id=?");
            statement.setLong(1, gid);
            ResultSet res = statement.executeQuery();
            while (res.next()) {
                Long uid = res.getLong(1);
                User user = UserDao.selectUserById(uid);
                users.add(user);
            }
            return users;
        } catch (SQLException e) {
            e.printStackTrace();
            return new ArrayList<>();
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 查找群聊最近消息
     *
     * @param gid 群id
     * @return ArrayList<Message> 消息列表
     */
    public static ArrayList<Message> groupRecentMessage(Long gid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {//"select * from message where m_group=? order by m_time desc limit 0,49"
            statement = con.prepareStatement("select * from message where m_group=? group by m_send_uid,message_text,m_group limit 0,49");
            
            statement.setLong(1, gid);
            ResultSet res = statement.executeQuery();
            ArrayList<Message> messages = new ArrayList<Message>();
            while (res.next()) {
                Message message = new Message(res.getLong(1), res.getLong(4), gid, res.getLong(6),
                        res.getString(2), new Date(res.getTimestamp(3).getTime()),
                        res.getInt(7), res.getBoolean(8));
                messages.add(message);
            }
            return messages;
        } catch (SQLException e) {
            e.printStackTrace();
            return new ArrayList<>();
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 创建群聊
     *
     * @param uid       群内用户id
     * @param groupName 群聊名称
     * @return gid 群id
     */
    public static Long createGroup(ArrayList<Long> uid, String groupName) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        Long gid = null;
        try {
            statement = con.prepareStatement("insert into `group`(g_name, g_createtime) values (?,?) ", Statement.RETURN_GENERATED_KEYS);
            statement.setString(1, groupName);
            statement.setTimestamp(2, new Timestamp(new Date().getTime()));
            statement.executeUpdate();
            ResultSet res = statement.getGeneratedKeys();
            if (res.next()) {
                gid = res.getLong(1);
                for (Long a : uid) {
                    statement = con.prepareStatement("insert into user_in_group(userid, group_id) values (?,?)");
                    statement.setLong(1, a);
                    statement.setLong(2, gid);
                    statement.executeUpdate();
                }
            }
            return gid;
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        } finally {
            DBUtil.close(statement, con);
        }
        
    }
}
