package Client.View.entity;

import Common.entity.Notice;
import Common.entity.User;

import java.util.Date;

public class NoticeItem extends Notice {
    private static final long serialVersionUID = -5098862071285956817L;
    private User fromUser;
    
    public NoticeItem(User fromUser, Long getId, Date time, String content, int type) {
        super(fromUser.getUid(), getId, time, content, type);
        this.fromUser = fromUser;
    }
    
    public User getFromUser() {
        return fromUser;
    }
}
