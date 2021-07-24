package Common.entity;

import java.io.Serializable;

/**
 * 这是一个类 代表处理请求的实体
 *
 * @author Java_Team
 * @version 1.5
 */
public enum ResponseType implements Serializable {
    OK, WRONG, CREATED, SERVERERROR
}
