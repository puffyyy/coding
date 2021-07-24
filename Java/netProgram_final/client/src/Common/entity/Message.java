package Common.entity;

import java.io.Serializable;
import java.util.Date;

/**
 * 这是一个,代表消息实体
 *
 * @author Java_Team
 * @version 1.5
 */
public class Message implements Serializable {
    private static final long serialVersionUID = -3754166292635335848L;
    
    private boolean isRead;
    private Long messageId;
    private Long fromUserId;
    private Long groupId;
    private Long toUserId;
    private String content;
    private Date sendTime;
    private int type;
    
    public Message() {
    }
    
    public Message(Long fromUserId, Long groupId, String content, Date sendTime) {
        this.fromUserId = fromUserId;
        this.groupId = groupId;
        this.content = content;
        this.sendTime = sendTime;
    }
    
    public Message(Long fromUserId, Long groupId, String content, Date sendTime, int type) {
        this.fromUserId = fromUserId;
        this.groupId = groupId;
        this.content = content;
        this.sendTime = sendTime;
        this.type = type;
    }
    
    public Message(Long messageId, Long fromUserId, Long groupId, Long toUserId, String content, Date sendTime, int type, boolean isRead) {
        this.messageId = messageId;
        this.fromUserId = fromUserId;
        this.groupId = groupId;
        this.toUserId = toUserId;
        this.content = content;
        this.sendTime = sendTime;
        this.type = type;
        this.isRead = isRead;
    }
    
    public Long getMessageId() {
        return messageId;
    }
    
    public void setMessageId(Long messageId) {
        this.messageId = messageId;
    }
    
    public Long getGroupId() {
        return groupId;
    }
    
    public void setGroupId(Long groupId) {
        this.groupId = groupId;
    }
    
    public int getType() {
        return type;
    }
    
    public void setType(int type) {
        this.type = type;
    }
    
    public Long getFromUserId() {
        return fromUserId;
    }
    
    public void setFromUserId(Long fromUserId) {
        this.fromUserId = fromUserId;
    }
    
    public Long getToUserId() {
        return toUserId;
    }
    
    public void setToUserId(Long toUserId) {
        this.toUserId = toUserId;
    }
    
    public String getContent() {
        return content;
    }
    
    public void setContent(String content) {
        this.content = content;
    }
    
    public Date getSendTime() {
        return sendTime;
    }
    
    public void setSendTime(Date sendTime) {
        this.sendTime = sendTime;
    }
    
    public boolean isRead() {
        return isRead;
    }
    
    public void setRead(boolean read) {
        isRead = read;
    }
    
    @Override
    public String toString() {
        return "Message{" +
                "fromUserId=" + fromUserId +
                ", groupId=" + groupId +
                ", toUserId=" + toUserId +
                ", content='" + content + '\'' +
                ", sendTimeStamp=" + sendTime +
                '}';
    }
}
