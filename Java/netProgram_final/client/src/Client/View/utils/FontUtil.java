package Client.View.utils;

import java.awt.*;

/**
 * 默认字体
 */
public class FontUtil {
    private static final Font font;
    
    static {
        
        font = new Font("微软雅黑", Font.PLAIN, 14);//PingFang SC
    }
    
    public static Font getDefaultFont() {
        return getDefaultFont(14, Font.PLAIN);
    }
    
    public static Font getDefaultFont(int size) {
        return getDefaultFont(size, Font.PLAIN);
    }
    
    public static Font getDefaultFont(int size, int style) {
        return font.deriveFont(style, size);
        //return new Font("YaHei Consolas Hybrid",  style, size);
        //return new Font("微软雅黑", style, size);
    }
    
}
