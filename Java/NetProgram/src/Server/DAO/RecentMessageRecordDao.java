package Server.DAO;

import Common.entity.Message;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

public class RecentMessageRecordDao {
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

    public static ArrayList<Message> groupMessage(Long gid){
        Connection con =DBUtil.getConn();
        PreparedStatement statement = null;
        try{
            statement= con.prepareStatement("select * from message where m_group=? order by m_time desc ");
            statement.setLong(1,gid);
            ResultSet res = statement.executeQuery();
            ArrayList<Message> messages = new ArrayList<>();
            while(res.next()){
                Message message =new Message(res.getLong(1),res.getLong(4),gid,res.getLong(6),
                        res.getString(2),new Date(res.getTimestamp(3).getTime()),res.getInt(7));
                messages.add(message);
            }
            return messages;
        }catch (SQLException e){
            e.printStackTrace();
            return null;
        }
        finally {
            DBUtil.close(statement,con);
        }
    }

//    后面改成group message 的map
//    public static HashMap<Long, Message> getRecentMessage(Long uid){
//        Connection con = DBUtil.getConn();
//        PreparedStatement statement = null;
//        try {
//            statement = con.prepareStatement("select  message_text, m_time, m_send_uid, m_group, m_type " +
//                    "from message where message.m_get_uid=? limit 0,20");
//            HashMap<Long,Message> messageList = new HashMap<Long, Message>();
//            ResultSet res = statement.executeQuery();
//            while (res.next()) {
//                Long from_uid = res.getLong(3);
//                String mes = res.getString(1);
//                Date sendDate = new Date(res.getTimestamp(2).getTime());
//                Long from_gid = res.getLong(4);
//                int type=res.getInt(5);
//                Message message = new Message(from_uid,from_gid,uid,mes,sendDate,type);
//            }
//        } catch (SQLException e) {
//            e.printStackTrace();
//        } finally {
//            DBUtil.close(statement, con);
//        }
//    }
}
