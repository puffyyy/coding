package Client.View.component;

import Client.View.utils.Colors;
import Client.View.utils.FontUtil;

import javax.swing.*;
import javax.swing.plaf.basic.BasicScrollBarUI;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.RoundRectangle2D;

public class MyScrollBarUI extends BasicScrollBarUI {
    
    @Override
    protected void configureScrollBarColors() {
        trackColor = Colors.ROOM_ITEM_GREY;
        setThumbBounds(0, 0, 3, 10);
    }

    /**
     * 重写方法，在原组件中新设置一个矩形区域，并且返回原组件区域
     * @param c 组件，这里指输入文本框滑块
     * @return 滑块宽度和高度组成的区域
     */
    @Override
    public Dimension getPreferredSize(JComponent c) {
        c.setPreferredSize(new Dimension(5, 0));
        return super.getPreferredSize(c);
    }
    // 重绘滑块的滑动区域背景

    /**
     * 重绘滑块区域背景
     * @param g 滑块区域原绘图
     * @param c 滑块组件
     * @param trackBounds 矩形区域
     */
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

    /**
     * 绘制选中滑块时的样式
     * @param g 滑块区域原绘图
     * @param c 滑块组件
     * @param thumbBounds 新设定的区域范围
     */
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

    /**
     * 新建增加的按钮
     * @param orientation 用int代表定向
     * @return 返回增加的按钮JButton
     */
    @Override
    protected JButton createIncreaseButton(int orientation) {
        JButton button = new JButton();
        button.setBorderPainted(false);
        button.setContentAreaFilled(false);
        button.setBorder(null);
        return button;
        
    }

    /**
     * 新建减少的按钮
     * @param orientation 用int代表定向
     * @return 返回减少的按钮JButton
     */
    @Override
    protected JButton createDecreaseButton(int orientation) {
        JButton button = new JButton();
        button.setBorderPainted(false);
        button.setContentAreaFilled(false);
        button.setFocusable(false);
        button.setBorder(null);
        return button;
    }
    
    public static class MyButton extends JButton {
        private static final long serialVersionUID = 39082560987930759L;
        private Color BUTTON_COLOR1 = new Color(236, 236, 236);
        private Color BUTTON_COLOR2 = new Color(228, 228, 228);
        private Color BUTTON_COLOR3 = new Color(216, 216, 216);
        private Color borderColor = new Color(193, 193, 193);
        
        public static final Color BUTTON_FOREGROUND_COLOR = Color.WHITE;
        private boolean hover;
    
        /**
         * RC组件中的按钮构造方法
         * @param title 标题
         * @param normal 颜色—正常
         * @param hover 颜色-待选
         * @param press 颜色-按压
         */
        public MyButton(String title, Color normal, Color hover, Color press) {
            this(title);
            this.BUTTON_COLOR1 = normal;
            this.BUTTON_COLOR2 = hover;
            this.BUTTON_COLOR3 = press;
            this.borderColor = press;
        }
    
        /**
         * RC组件中的按钮构造方法
         * @param name 按钮名称
         */
        public MyButton(String name) {
            this.setText(name);
            setFont(FontUtil.getDefaultFont(14));
            setBorderPainted(false);
            setForeground(BUTTON_FOREGROUND_COLOR);
            setFocusPainted(false);
            setContentAreaFilled(false);
            addMouseListener(new MouseAdapter() {
                @Override
                public void mouseEntered(MouseEvent e) {
                    hover = true;
                    setCursor(new Cursor(Cursor.HAND_CURSOR));
                    repaint();
                }
                
                @Override
                public void mouseExited(MouseEvent e) {
                    hover = false;
                    repaint();
                }
            });
        }
    
        /**
         * 绘图RC按钮组件
         * @param g 初始绘图
         */
        @Override
        protected void paintComponent(Graphics g) {
            Graphics2D g2d = (Graphics2D) g.create();
            int h = getHeight();
            int w = getWidth();
            
            GradientPaint gp;
            
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                    RenderingHints.VALUE_ANTIALIAS_ON);
            
            if (getModel().isPressed()) {
                gp = new GradientPaint(0.0F, 0.0F, BUTTON_COLOR3, 0.0F,
                        h, BUTTON_COLOR3, true);
            } else {
                if (hover) {
                    gp = new GradientPaint(0.0F, 0.0F, BUTTON_COLOR2, 0.0F,
                            h, BUTTON_COLOR2, true);
                } else {
                    gp = new GradientPaint(0.0F, 0.0F, BUTTON_COLOR1, 0.0F,
                            h, BUTTON_COLOR1, true);
                }
            }
            
            RoundRectangle2D.Float r2d = new RoundRectangle2D.Float(0, 0, w - 1,
                    h - 1, 4, 4);
            Shape clip = g2d.getClip();
            g2d.clip(r2d);
            
            g2d.setPaint(gp);
            g2d.fillRect(0, 0, w, h);
            g2d.setClip(clip);
            
            g2d.setColor(borderColor);
            g2d.drawRoundRect(0, 0, w - 2, h - 2, 5, 5);
            g2d.dispose();
            super.paintComponent(g);
        }
    }
}