package Server.Service;

import Common.entity.Message;
import Server.DAO.GroupDao;

import java.util.ArrayList;

public class RecentMessageRecordService {
    public static ArrayList<Message> recentMessageOfGroup(Long gid){
        return GroupDao.groupRecentMessage(gid);
    }

    
}
