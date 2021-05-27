package Server.Service;

import Common.entity.Message;

import java.util.ArrayList;

import static Server.DAO.OfflineMessageDao.deleteOfflineMessageByUserId;
import static Server.DAO.OfflineMessageDao.getOfflineMessageById;

public class OfflineMessageService {
    public ArrayList<Message> selectOfflineMessageById(Long uid) {
        return getOfflineMessageById(uid);
    }
    
    public void removeOfflineMessageById(Long uid) {
        deleteOfflineMessageByUserId(uid);
    }
    
    public void setOfflineMessage(Message message) {
//        Object[] arr = new Object[]{message.getFromUserId(),
//                message.getToUserId(), message.getContent(), new Timestamp(message.getSendTimeStamp().getTime())};
//        insertOfflineMessage(arr);
    }
}
