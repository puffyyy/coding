package Common.entity;

import java.io.Serializable;

/**
 * 这是一个枚举类 枚举请求的类别
 *
 * @author Java_Team
 * @version 1.5
 */
public enum RequestType implements Serializable {
    REGISTER,
    LOGIN,
    LOGOUT,
    SEND_MESSAGE,
    STATE,
    CHANGE_AVATAR,
    CHANGE_PASSWORD,
    ADD_FRIEND,
    JOIN_GROUP,
}
