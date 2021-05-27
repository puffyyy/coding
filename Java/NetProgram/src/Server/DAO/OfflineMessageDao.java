package Server.DAO;

import Common.entity.Message;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;

public class OfflineMessageDao {
    public static ArrayList<Message> getOfflineMessageById(Long uid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("SELECT message_text,m_time,m_send_uid,m_group,m_type " +
                    "FROM unreceived_message,message WHERE user_id = ? and message.mid=unreceived_message.message_id");
            statement.setLong(1, uid);
            ArrayList<Message> messageList = new ArrayList<>();
            ResultSet res = statement.executeQuery();
            while (res.next()) {
                Long from_uid = res.getLong(3);
                String mes = res.getString(1);
                Date sendDate = new Date(res.getTimestamp(2).getTime());
                Long from_gid = res.getLong(4);
                int type=res.getInt(5);
                //warning  null message id
                messageList.add(new Message(null,from_uid,from_gid, uid, mes, sendDate,type));
            }
            return messageList;
        } catch (SQLException | NumberFormatException e) {
            e.printStackTrace();
            return null;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    public static void deleteOfflineMessageByUserId(Long uid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("delete from unreceived_message where user_id = ?");
            statement.setLong(1, uid);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    public static void insertOfflineMessage(Object[] arr) {
        if (arr.length != 4)
            return;
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("insert into unreceived_message(user_id,message_id) values (?,?)");
            //可能存在问题
            for (int i = 1; i <= 2; i++) {
                statement.setObject(i, arr[i - 1]);
            }
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(statement, con);
        }
    }
}
