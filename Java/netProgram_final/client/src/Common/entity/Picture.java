package Common.entity;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

/**
 * 这是一个类 代表图片实体
 *
 * @author Java_Team
 * @version 1.5
 */
public class Picture implements Serializable {
    
    transient BufferedImage img;
    private static final long serialVersionUID = -7738291202507506957L;
    
    private void writeObject(ObjectOutputStream out) throws IOException {
        out.defaultWriteObject();
        ImageIO.write(img, "png", out);
    }
    
    private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
        in.defaultReadObject();
        img = ImageIO.read(in);
    }
    
    public BufferedImage getImg() {
        return img;
    }
    
    public void setImg(BufferedImage img) {
        this.img = img;
    }
}
