package Common.entity;

import java.io.Serializable;
import java.util.Date;

/**
 * 这是一个类 代表通知消息实体
 *
 * @author Java_Team
 * @version 1.5
 */
public class Notice implements Serializable {
    private static final long serialVersionUID = -375749238335848L;
    private Long nid;
    private Long sendId;
    private Long getId;
    private Date time;
    private String content;
    private int type;
    
    public Notice(Long sendId, Long getId, Date time, String content, int type) {
        this.sendId = sendId;
        this.getId = getId;
        this.time = time;
        this.content = content;
        this.type = type;
    }
    
    public Notice(Long nid, Long sendId, Long getId, Date time, String content, int type) {
        this.nid = nid;
        this.sendId = sendId;
        this.getId = getId;
        this.time = time;
        this.content = content;
        this.type = type;
    }
    
    public Long getNid() {
        return nid;
    }
    
    public void setNid(Long nid) {
        this.nid = nid;
    }
    
    public Long getSendId() {
        return sendId;
    }
    
    public void setSendId(Long sendId) {
        this.sendId = sendId;
    }
    
    public Long getGetId() {
        return getId;
    }
    
    public void setGetId(Long getId) {
        this.getId = getId;
    }
    
    public Date getTime() {
        return time;
    }
    
    public void setTime(Date time) {
        this.time = time;
    }
    
    public String getContent() {
        return content;
    }
    
    public void setContent(String content) {
        this.content = content;
    }
    
    public int getType() {
        return type;
    }
    
    public void setType(int type) {
        this.type = type;
    }
    
    @Override
    public String toString() {
        return "Notice{" +
                "nid=" + nid +
                ", sendId=" + sendId +
                ", getId=" + getId +
                ", time=" + time +
                ", content='" + content + '\'' +
                ", type=" + type +
                '}';
    }
}
