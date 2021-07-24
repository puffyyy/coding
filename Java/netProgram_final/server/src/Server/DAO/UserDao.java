package Server.DAO;

import Common.entity.Group;
import Common.entity.User;

import java.sql.*;
import java.util.ArrayList;

/**
 * 这是一个类 在数据库层面处理用户信息事务
 *
 * @author Java_Team
 * @version 1.5
 */

public class UserDao {
    
    /**
     * 初始化用户登录后的会话界面
     *
     * @param uid 用户id
     * @return groups 所在群聊列表
     */
    public static ArrayList<Group> initialGroup(Long uid) {
        ArrayList<Group> groups = new ArrayList<Group>();
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("select group_id from user_in_group " +
                    "where userid=?");
            statement.setLong(1, uid);
            ResultSet res = statement.executeQuery();
            while (res.next()) {
                Long gid = res.getLong(1);
                Group group = new Group();
                group = GroupDao.selectGroupByGid(gid);
                groups.add(group);
            }
            GroupDao.sortInMessageTime(groups);
            MessageDao.setMessageRead(uid);
            return groups;
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 通过用户id查找指定用户
     *
     * @param uid 用户id
     * @return user 用户实体
     */
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
    
    /**
     * 通过关键字查找用户
     *
     * @param key 关键字
     * @return users 含关键字的用户列表
     */
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
    
    /**
     * 删除指定用户
     *
     * @param uid 用户id
     */
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
    
    /**
     * 新建用户
     *
     * @param arr 用户信息
     * @return uid 用户主键id
     */
    public static Long insertUser(Object[] arr) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        if (arr.length != 5) return null;
        try {
            statement = con.prepareStatement("insert into user(username,password,sex,avatar_path,phone_num) " +
                    "values(?,?,?,?,?)", Statement.RETURN_GENERATED_KEYS);
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
    
    /**
     * 修改用户昵称
     *
     * @param uid  用户id
     * @param name 新昵称
     * @return bool 是否成功
     */
    public static boolean modifyUsername(Long uid, String name) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("update user set username=? where uid=?");
            statement.setString(1, name);
            statement.setLong(2, uid);
            int rows = statement.executeUpdate();
            return rows > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 修改用户密码
     *
     * @param uid  用户id
     * @param pass 新密码
     * @return bool 是否成功
     */
    public static boolean modifyPassword(Long uid, String pass) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("update user set password=? where uid=?");
            statement.setString(1, pass);
            statement.setLong(2, uid);
            int rows = statement.executeUpdate();
            return rows > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 修改用户头像
     *
     * @param uid  用户id
     * @param path 新头像存储路径
     * @return bool 是否成功
     */
    public static boolean modifyAvatar(Long uid, String path) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("update user set avatar_path=? where uid=?");
            statement.setString(1, path);
            statement.setLong(2, uid);
            int rows = statement.executeUpdate();
            return rows > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        } finally {
            DBUtil.close(statement, con);
        }
    }
    
    /**
     * 修改用户手机号
     *
     * @param uid 用户id
     * @param num 新号码
     * @return bool 是否成功
     */
    public static boolean modifyPhone(Long uid, String num) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("update user set phone_num=? where uid=?");
            statement.setString(1, num);
            statement.setLong(2, uid);
            int rows = statement.executeUpdate();
            return rows > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        } finally {
            DBUtil.close(statement, con);
        }
    }
}
