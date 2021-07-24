package Server.DAO;

import java.sql.*;

/**
 * 这是一个类 数据库连接与关闭的相关处理
 *
 * @author Java_Team
 * @version 1.5
 */

public class DBUtil {
    public static String db_name;
    public static String db_user;
    public static String db_pass;
    
    /**
     * 连接指定数据库
     *
     * @param
     * @return Connection
     */
    public static Connection getConn() {
        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            String db_url = "jdbc:mysql://localhost:3306/" + db_name + "?useUnicode=true&characterEncoding=utf8";
            conn = DriverManager.getConnection(db_url, db_user, db_pass);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return conn;
    }
    
    public static void close(Statement state, Connection conn) {
        if (state != null) {
            try {
                state.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        if (conn != null) {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
    
    public static void close(ResultSet rs) {
        if (rs != null) {
            try {
                rs.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
    
    public static void close(Statement state) {
        if (state != null) {
            try {
                state.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
    
    public static void close(ResultSet rs, Statement state, Connection conn) {
        close(rs);
        close(state, conn);
    }
    
}
