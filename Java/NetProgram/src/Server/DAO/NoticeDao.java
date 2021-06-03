package Server.DAO;

import Common.entity.Notice;

import java.sql.*;
import java.util.ArrayList;
import java.util.Date;

/**
 * 这是一个类 在数据库层面处理通知消息的发送与接收
 *
 * @author Java_Team
 * @version 1.5
 */

public class NoticeDao {
    /**
     * 通过通知消息id查找用户离线时收到的通知
     *
     * @param uid 用户id
     * @return notices 通知列表
     */
    public static ArrayList<Notice> searchNotice(Long uid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        ArrayList<Notice> notices = new ArrayList<>();
        try {
            statement = con.prepareStatement("select * from notice where get_uid=?");
            statement.setLong(1, uid);
            ResultSet res = statement.executeQuery();
            while (res.next()) {
                long nid, s_id, g_id;
                Date time;
                int type;
                String content;
                nid = res.getLong(1);
                s_id = res.getLong(2);
                g_id = res.getLong(3);
                time = new Date(res.getTimestamp(4).getTime());
                content = res.getString(5);
                type = res.getInt(6);
                Notice notice = new Notice(nid, s_id, g_id, time, content, type);
                notices.add(notice);
            }
            statement = con.prepareStatement("delete from notice where get_uid=?");
            statement.setLong(1, uid);
            statement.executeUpdate();
            return notices;
        } catch (SQLException e) {
            e.printStackTrace();
            return notices;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 向离线用户插入通知记录
     *
     * @param notice 通知实体
     */
    public static void insertNotice(Notice notice) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("insert into notice(send_uid, get_uid, time, content, type) values (?,?,?,?,?)");
            statement.setLong(1, notice.getSendId());
            statement.setLong(2, notice.getGetId());
            statement.setTimestamp(3, new Timestamp(notice.getTime().getTime()));
            statement.setString(4, notice.getContent());
            statement.setInt(5, notice.getType());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(statement, con);
        }
    }
}
