package Server.DAO;

import Common.entity.Group;
import Common.entity.User;

import java.sql.*;
import java.util.ArrayList;

public class UserDao {
    
    public static ArrayList<Group> initialGroup(Long uid) {
        ArrayList<Group> groups = new ArrayList<>();
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("select group_id from user_in_group " +
                    "where userid=?");
            statement.setLong(1, uid);
            ResultSet res = statement.executeQuery();
            while (res.next()) {
                Long gid = res.getLong(1);
                Group group = GroupDao.selectGroupByGid(gid);
                groups.add(group);
            }
            GroupDao.sortInMessageTime(groups);
            return groups;
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    public static User selectUserById(Long uid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("SELECT * FROM user WHERE uid = ?");
            statement.setLong(1, uid);
            ResultSet res = statement.executeQuery();
            if (res.next()) {
                String name = res.getString(2);
                String pwd = res.getString(3);
                String sex = res.getString(4);
                String path = res.getString(5);
                String num = res.getString(6);
                return new User(uid, name, pwd, sex.charAt(0), num, path);
            } else {
                return null;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    public static ArrayList<User> selectUserByKeyWords(String key) {
        ArrayList<User> arr = new ArrayList<User>();
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            String read = "%" + key + "%";
            String sql = "select * from user where username like '" + read + "' or phone_num like '" + read + "'";
            statement = con.prepareStatement(sql);
            ResultSet res = statement.executeQuery();
            while (res.next()) {
                Long uid = res.getLong(1);
                String name = res.getString(2);
                String pass = res.getString(3);
                char gender = res.getString(4).charAt(0);
                String path = res.getString(5);
                String num = res.getString(6);
                User friend = new User(uid, name, pass, gender, num, path);
                arr.add(friend);
            }
            return arr;
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    public static void deleteUserById(Long uid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("delete from user where uid = ?");
            statement.setLong(1, uid);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    public static Long insertUser(Object[] arr) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        if (arr.length != 5) return null;
        try {
            statement = con.prepareStatement("insert into user(username,password,sex,avatar_path,phone_num) " +
                    "values(?,?,?.?.?)", Statement.RETURN_GENERATED_KEYS);
            statement.setString(1, (String) arr[0]);
            statement.setString(2, (String) arr[1]);
            statement.setString(3, (String) arr[2]);
            statement.setString(4, (String) arr[3]);
            statement.setString(5, (String) arr[4]);
            statement.executeUpdate();
            ResultSet rs = statement.getGeneratedKeys();
            if (rs.next()) {
                return rs.getLong(1);
            }
            return null;
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        } finally {
            DBUtil.close(statement, con);
        }
        
    }
    
    //登录布局，创建群聊
    
}
