package Server.Service;

import Common.entity.Notice;
import Common.entity.User;
import Server.DAO.NoticeDao;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * 这是一个类 提供通知处理的方法
 *
 * @author Java_Team
 * @version 1.5
 */

public class NoticeService {
    /**
     * 查询用户离线期间的通知信息
     *
     * @param uid 用户id
     * @return map 通知信息和用户键值对
     */
    public static HashMap<Notice, User> getNotice(Long uid) {
        HashMap<Notice, User> map = new HashMap<>();
        ArrayList<Notice> list = NoticeDao.searchNotice(uid);
        for (Notice n : list) {
            map.put(n, UserService.selectUserById(n.getSendId()));
        }
        return map;
    }
    
    /**
     * 发送notice
     *
     * @param notice 消息实体
     */
    public static void sendNotice(Notice notice) {
        NoticeDao.insertNotice(notice);
    }
}
