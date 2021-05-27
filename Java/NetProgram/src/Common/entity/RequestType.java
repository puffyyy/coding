package Common.entity;

import java.io.Serializable;

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
