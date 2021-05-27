package Common.entity;

import java.io.Serializable;

public class File implements Serializable {
    private static final long serialVersionUID = -7463865758784067421L;
    String fileName;
    String fileType;
    private Long fromUserId;
    private Long groupId;
    private Long toUserId;
    
    private byte[] data;
    
    public File(String fileName, String fileType) {
        this.fileName = fileName;
        this.fileType = fileType;
    }
    
    public void setData(byte[] data) {
        this.data = data;
    }
    
    public byte[] getData() {
        return data;
    }
    
}