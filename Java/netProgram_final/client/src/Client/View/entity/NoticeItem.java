package Client.View.entity;

import Common.entity.Notice;
import Common.entity.User;

import java.util.Date;

public class NoticeItem extends Notice {
    private static final long serialVersionUID = -5098862071285956817L;
    private User fromUser;

    /**
     * 通知消息实体项构造方法
     * @param fromUser 通知来源用户
     * @param getId 通知ID
     * @param time 通知时间
     * @param content 通知内容
     * @param type 通知类型，以int表示
     */
    public NoticeItem(User fromUser, Long getId, Date time, String content, int type) {
        super(fromUser.getUid(), getId, time, content, type);
        this.fromUser = fromUser;
    }
    
    public User getFromUser() {
        return fromUser;
    }
}
