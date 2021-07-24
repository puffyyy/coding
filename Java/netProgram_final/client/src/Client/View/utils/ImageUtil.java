package Client.View.utils;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.RoundRectangle2D;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.URL;

/**
 * 处理图像基本功能
 */
public class ImageUtil {
    public static BufferedImage setRadius(Image srcImage, int width, int height, int radius) throws IOException {
        
        if (srcImage.getWidth(null) > width || srcImage.getHeight(null) > height) {
            // 图片过大，进行缩放
            ImageIcon imageIcon = new ImageIcon();
            imageIcon.setImage(srcImage.getScaledInstance(width, height, Image.SCALE_SMOOTH));
            srcImage = imageIcon.getImage();
        }
        
        BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        Graphics2D gs = image.createGraphics();
        gs.setComposite(AlphaComposite.Src);
        gs.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        gs.setColor(Color.WHITE);
        gs.fill(new RoundRectangle2D.Float(0, 0, width, height, radius, radius));
        gs.setComposite(AlphaComposite.SrcAtop);
        gs.drawImage(srcImage, 0, 0, null);
        gs.dispose();
        return image;
    }
    
    public static BufferedImage toBufferedImage(Image image) {
        if (image instanceof BufferedImage) {
            return (BufferedImage) image;
        }
        image = new ImageIcon(image).getImage();
        BufferedImage bimage = null;
        GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
        try {
            int transparency = Transparency.OPAQUE;
            GraphicsDevice gs = ge.getDefaultScreenDevice();
            GraphicsConfiguration gc = gs.getDefaultConfiguration();
            bimage = gc.createCompatibleImage(
                    image.getWidth(null), image.getHeight(null), transparency);
        } catch (HeadlessException e) {
            e.printStackTrace();
        }
        
        if (bimage == null) {
            int type = BufferedImage.TYPE_INT_RGB;
            bimage = new BufferedImage(image.getWidth(null), image.getHeight(null), type);
        }
        Graphics g = bimage.createGraphics();
        g.drawImage(image, 0, 0, null);
        g.dispose();
        return bimage;
    }
    
    public static ImageIcon getIcon(Object context, String path, int width, int height) {
        ImageIcon imageIcon;
        URL url = context.getClass().getResource(path);
        if (url == null) {
            return null;
        }
        imageIcon = new ImageIcon(url);
        if (width > 0 && height > 0) {
            imageIcon.setImage(imageIcon.getImage().getScaledInstance(width, height, Image.SCALE_SMOOTH));
        }
        
        return imageIcon;
    }
}
