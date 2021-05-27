package Server.DAO;

import Common.entity.Group;
import Common.entity.Message;
import Common.entity.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;

public class GroupDao {
    public static void sortInMessageTime(ArrayList<Group> groups) {
        groups.sort((p, q) -> {
            if (p.messages != null && q.messages != null && p.messages.size() > 0 && q.messages.size() > 0)
                return q.messages.get(0).getSendTime().compareTo(p.messages.get(0).getSendTime());
            return p.messages == null || p.messages.size() == 0 ? 1 : -1;
        });
    }
    
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
            ArrayList<Message> messages;
            messages = RecentMessageRecordDao.groupMessage(gid);
            return new Group(gid, name, path, users, messages);
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    public static ArrayList<Message> groupRecentMessage(Long gid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("select * from message where m_group=? order by m_time desc limit 0,49");
            statement.setLong(1, gid);
            ResultSet res = statement.executeQuery();
            ArrayList<Message> messages = new ArrayList<Message>();
            while (res.next()) {
                Message message = new Message(res.getLong(1), res.getLong(4), gid, res.getLong(6),
                        res.getString(2), new Date(res.getTimestamp(3).getTime()), res.getInt(7));
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
}
