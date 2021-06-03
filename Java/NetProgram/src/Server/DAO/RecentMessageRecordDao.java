package Server.DAO;

import Common.entity.Message;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;

/**
 * 这是一个类 在数据库层面处理消息记录
 *
 * @author Java_Team
 * @version 1.5
 */

public class RecentMessageRecordDao {
    /**
     * 已弃用
     *
     * @deprecated
     */
    public static void insertMessage(Object[] arr) {
        if (arr.length != 6)
            return;
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("insert into message(message_text, m_time, m_send_uid, m_group, m_get_uid, m_type) " +
                    "values (?,?,?,?,?,?)");
            for (int i = 1; i <= 6; i++) {
                statement.setObject(i, arr[i - 1]);
            }
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 查询群聊消息
     *
     * @param gid 群id
     * @return messages 消息列表
     */
    public static ArrayList<Message> groupMessage(Long gid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("select * from message where m_group=? group by m_send_uid,message_text,m_group,m_time order by m_time");
            statement.setLong(1, gid);
            ResultSet res = statement.executeQuery();
            ArrayList<Message> messages = new ArrayList<>();
            while (res.next()) {
                Message message = new Message(res.getLong(1), res.getLong(4),
                        gid, res.getLong(6), res.getString(2),
                        new Date(res.getTimestamp(3).getTime()),
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
    
}
