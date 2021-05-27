package Server.DAO;

import Common.entity.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class FriendDao {
    public static ArrayList<User> friendList(Long uid){
        Connection con = DBUtil.getConn();
        PreparedStatement statement;
        try{
            statement = con.prepareStatement("select uid,username,password,sex,avatar_path,phone_num from user,friends " +
                    "where user_id=? and user.uid=friends.friend_id");
            statement.setLong(1,uid);
            ResultSet res = statement.executeQuery();
            ArrayList<User> arr = new ArrayList<User>();
            while(res.next()){
                Long fuid = res.getLong(1);
                String name = res.getString(2);
                String pass = res.getString(3);
                char gender = res.getString(4).charAt(0);
                String path = res.getString(5);
                String num =res.getString(6);
                User friend = new User(fuid,name,pass,gender,num,path);
                arr.add(friend);
            }
            DBUtil.close(res);
            DBUtil.close(statement);
            statement = con.prepareStatement("select uid,username,password,sex,avatar_path,phone_num from user,friends " +
                    "where friend_id=? and user.uid=friends.user_id");
            statement.setLong(1,uid);
            res = statement.executeQuery();
            while(res.next()){
                Long fuid = res.getLong(1);
                String name = res.getString(2);
                String pass = res.getString(3);
                char gender = res.getString(4).charAt(0);
                String path = res.getString(5);
                String num =res.getString(6);
                User friend = new User(fuid,name,pass,gender,num,path);
                arr.add(friend);
            }
            DBUtil.close(res);
            DBUtil.close(statement);
            return arr;
        }catch (SQLException e) {
            e.printStackTrace();
            return new ArrayList<User>();
        } finally {
            DBUtil.close(null, con);
        }
    }

    public static ArrayList<Long> selectFriendsById(Long uid) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement;
        try {
            statement = con.prepareStatement("SELECT * FROM friends WHERE user_id = ?");
            statement.setLong(1, uid);
            ResultSet res = statement.executeQuery();
            ArrayList<Long> arr = new ArrayList<>();
            while (res.next()) {
                Long friendId = res.getLong(2);
                arr.add(friendId);
            }
            DBUtil.close(res);
            DBUtil.close(statement);
            statement = con.prepareStatement("SELECT * FROM friends WHERE friend_id = ?");
            statement.setLong(1, uid);
            res = statement.executeQuery();
            while (res.next()) {
                Long friendId = res.getLong(2);
                arr.add(friendId);
            }
            DBUtil.close(res);
            DBUtil.close(statement);
            return arr;
        } catch (SQLException e) {
            e.printStackTrace();
            return new ArrayList<Long>();
        } finally {
            DBUtil.close(null, con);
        }
    }
    
    public static void insertFriend(Long friend1, Long friend2) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("insert into friends(user_id, friend_id) values(?,?)");
            statement.setLong(1, friend1);
            statement.setLong(2, friend2);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(statement, con);
        }
    }

    public static void deleteFriend(Long friend1, Long friend2) {
        Connection con = DBUtil.getConn();
        PreparedStatement statement = null;
        try {
            statement = con.prepareStatement("delete from friends where user_id = ? and friend_id = ?");
            statement.setLong(1, friend1);
            statement.setLong(2, friend2);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(statement, con);
        }
    }
}
