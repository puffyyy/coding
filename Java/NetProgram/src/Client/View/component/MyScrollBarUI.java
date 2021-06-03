package Client.View.component;

import Client.View.utils.Colors;

import javax.swing.*;
import javax.swing.plaf.basic.BasicScrollBarUI;
import java.awt.*;

public class MyScrollBarUI extends BasicScrollBarUI {
    
    @Override
    protected void configureScrollBarColors() {
        trackColor = Colors.ROOM_ITEM_GREY;
        setThumbBounds(0, 0, 3, 10);
    }
    
    @Override
    public Dimension getPreferredSize(JComponent c) {
        c.setPreferredSize(new Dimension(5, 0));
        return super.getPreferredSize(c);
    }
    // 重绘滑块的滑动区域背景
    
    public void paintTrack(Graphics g, JComponent c, Rectangle trackBounds) {
        Graphics2D g2 = (Graphics2D) g;
        GradientPaint gp = null;
        
        if (this.scrollbar.getOrientation() == JScrollBar.VERTICAL) {
            gp = new GradientPaint(0, 0, Colors.ROOM_ITEM_GREY, trackBounds.width, 0, Colors.ROOM_ITEM_GREY);
        } else if (this.scrollbar.getOrientation() == JScrollBar.HORIZONTAL) {
            gp = new GradientPaint(0, 0, new Color(80, 80, 80), trackBounds.height, 0, new Color(80, 80, 80));
        }
        
        g2.setPaint(gp);
        g2.fillRect(trackBounds.x, trackBounds.y, trackBounds.width, trackBounds.height);
        
        //绘制Track的边框
        /*       g2.setColor(new Color(175, 155, 95));
         g2.drawRect(trackBounds.x, trackBounds.y, trackBounds.width - 1,
                trackBounds.height - 1);
        */
        
        if (trackHighlight == BasicScrollBarUI.DECREASE_HIGHLIGHT)
            this.paintDecreaseHighlight(g);
        
        if (trackHighlight == BasicScrollBarUI.INCREASE_HIGHLIGHT)
            this.paintIncreaseHighlight(g);
    }
    
    @Override
    protected void paintThumb(Graphics g, JComponent c, Rectangle thumbBounds) {
        // 把绘制区的x，y点坐标定义为坐标系的原点
        g.translate(thumbBounds.x, thumbBounds.y);
        g.setColor(new Color(204, 201, 199));
        
        Graphics2D g2 = (Graphics2D) g;
        RenderingHints rh = new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        
        g2.addRenderingHints(rh);
        g2.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.5f));
        
        // 设置填充颜色，这里设置了渐变，由下往上
        // g2.setPaint(new GradientPaint(c.getWidth() / 2, 1, Color.GRAY,
        // c.getWidth() / 2, c.getHeight(), Color.GRAY));
        
        g2.fillRoundRect(0, 0, 6, thumbBounds.height - 1, 6, 6);
    }
    
    @Override
    protected JButton createIncreaseButton(int orientation) {
        JButton button = new JButton();
        button.setBorderPainted(false);
        button.setContentAreaFilled(false);
        button.setBorder(null);
        return button;
        
    }
    
    @Override
    protected JButton createDecreaseButton(int orientation) {
        JButton button = new JButton();
        button.setBorderPainted(false);
        button.setContentAreaFilled(false);
        button.setFocusable(false);
        button.setBorder(null);
        return button;
    }
    
}