package Server.Service;

import Common.entity.Message;
import Server.DAO.GroupDao;

import java.util.ArrayList;

/**
 * 这是一个类 提供消息记录的处理方法
 *
 * @author Java_Team
 * @version 1.5
 * @deprecated
 */

public class RecentMessageRecordService {
    public static ArrayList<Message> recentMessageOfGroup(Long gid) {
        return GroupDao.groupRecentMessage(gid);
    }
    
}
