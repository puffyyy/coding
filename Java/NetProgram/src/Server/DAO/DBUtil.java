package Server.DAO;

import java.sql.*;

public class DBUtil {
    public static String db_name = "netprogram";
    public static String db_url = "jdbc:mysql://localhost:3306/" + db_name + "?useUnicode=true&characterEncoding=utf8";
    public static String db_user = "root";
    public static String db_pass = "57913";
    
    public static Connection getConn() {
        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(db_url, db_user, db_pass);
//            System.out.println("db " + db_name + " connect success");
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
