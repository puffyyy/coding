package Server.DAO;

import Common.entity.Message;

import java.sql.*;
import java.util.ArrayList;

/**
 * 这是一个类 在数据库层面处理消息的发送与接收
 *
 * @author Java_Team
 * @version 1.5
 */

public class MessageDao {
    /**
     * 通过消息id查找对应消息
     *
     * @param mid 消息id
     * @return Message 消息实体对象
     */
    public static Message searchMessageInMid(Long mid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("select * from message where mid = ?");
            statement.setLong(1, mid);
            ResultSet res = statement.executeQuery();
            if (res.next()) {
                String content = res.getString(2);
                Long fuid, tuid, gid;
                fuid = res.getLong(4);
                gid = res.getLong(5);
                tuid = res.getLong(6);
                int type = res.getInt(7);
                Date sendTime = new Date(res.getTimestamp(3).getTime());
                boolean read = res.getBoolean(8);
                return new Message(mid, fuid, gid, tuid, content, sendTime, type, read);
            }
            return null;
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 将消息置为已读状态
     *
     * @param uid 用户id
     */
    public static void setMessageRead(Long uid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("update message set m_get = 1 where m_get_uid=? and m_get =0");
            statement.setLong(1, uid);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 将新消息插入数据库
     *
     * @param message 消息实体
     */
    public static void insertMessage(Message message) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("insert into message(message_text, m_time, m_send_uid, m_group, m_get_uid, m_type, m_get) " +
                    "values (?,?,?,?,?,?,?)");
            statement.setString(1, message.getContent());
            statement.setTimestamp(2, new Timestamp(message.getSendTime().getTime()));
            statement.setLong(3, message.getFromUserId());
            statement.setLong(4, message.getGroupId());
            statement.setLong(5, message.getToUserId());
            statement.setInt(6, message.getType());
            statement.setBoolean(7, message.isRead());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 通过关键字模糊查找消息
     *
     * @param key 关键字
     * @return messages 含关键字的消息列表
     */
    public static ArrayList<Message> searchMessage(String key) {
        ArrayList<Message> messages = new ArrayList<>();
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("select mid from message where message_text like '%" + key + "%'");
            ResultSet res = statement.executeQuery();
            while (res.next()) {
                Message message = searchMessageInMid(res.getLong(1));
                messages.add(message);
            }
            return messages;
        } catch (SQLException e) {
            e.printStackTrace();
            return messages;
        } finally {
            DBUtil.close(statement, con);
        }
    }
}
