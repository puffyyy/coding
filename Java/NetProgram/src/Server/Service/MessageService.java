package Server.Service;

import Common.entity.Message;
import Server.DAO.MessageDao;

import java.util.ArrayList;

/**
 * 这是一个类 提供消息处理的方法
 *
 * @author Java_Team
 * @version 1.5
 */

public class MessageService {
    /**
     * 查询消息
     *
     * @param mid 消息id
     * @return message 消息对象
     */
    public static Message searchMessageByMid(Long mid) {
        return MessageDao.searchMessageInMid(mid);
    }
    
    /**
     * 插入消息记录
     *
     * @param message 消息对象
     */
    public static void insertMessageRecords(Message message) {
        MessageDao.insertMessage(message);
    }
    
    /**
     * 关键字查找消息
     *
     * @param key 关键字
     * @return messages 消息列表
     */
    public static ArrayList<Message> searchMessageRecordsInKeywords(String key) {
        return MessageDao.searchMessage(key);
    }
}
