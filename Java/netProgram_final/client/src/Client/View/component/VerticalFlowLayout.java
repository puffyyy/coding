package Client.View.component;

import java.awt.*;

public class VerticalFlowLayout extends FlowLayout {
    
    public static final int TOP = 0;
    public static final int MIDDLE = 1;
    public static final int BOTTOM = 2;
    private static final long serialVersionUID = 916339535428014894L;
    
    int hgap;
    int vgap;
    boolean hfill;
    boolean vfill;
    
    public VerticalFlowLayout() {
        this(TOP, 5, 5, true, false);
    }
    
    public VerticalFlowLayout(boolean hfill, boolean vfill) {
        this(TOP, 5, 5, hfill, vfill);
    }
    
    public VerticalFlowLayout(int align) {
        this(align, 5, 5, true, false);
    }
    
    public VerticalFlowLayout(int align, boolean hfill, boolean vfill) {
        this(align, 0, 0, hfill, vfill);
    }
    
    public VerticalFlowLayout(int align,
                              int hgap, int vgap,
                              boolean hfill, boolean vfill) {
        setAlignment(align);
        this.hgap = hgap;
        this.vgap = vgap;
        this.hfill = hfill;
        this.vfill = vfill;
    }

    /**
     * 调整布局大小
     * @param target 目标组件
     * @return 调整后组件Dimension
     */
    public Dimension preferredLayoutSize(Container target) {
        Dimension tarsiz = new Dimension(0, 0);
        
        for (int i = 0; i < target.getComponentCount(); i++) {
            Component m = target.getComponent(i);
            if (m.isVisible()) {
                Dimension d = m.getPreferredSize();
                tarsiz.width = Math.max(tarsiz.width, d.width);
                if (i > 0) {
                    tarsiz.height += hgap;
                }
                tarsiz.height += d.height;
            }
        }
        Insets insets = target.getInsets();
        tarsiz.width += insets.left + insets.right + hgap * target.getComponentCount();
        tarsiz.height += insets.top + insets.bottom + vgap * target.getComponentCount();
        return tarsiz;
    }

    /**
     * 最小布局大小
     * @param target 目标组件
     * @return 最小布局Dimension
     */
    public Dimension minimumLayoutSize(Container target) {
        Dimension tarsiz = new Dimension(0, 0);
        
        for (int i = 0; i < target.getComponentCount(); i++) {
            Component m = target.getComponent(i);
            if (m.isVisible()) {
                Dimension d = m.getMinimumSize();
                tarsiz.width = Math.max(tarsiz.width, d.width);
                if (i > 0) {
                    tarsiz.height += vgap;
                }
                tarsiz.height += d.height;
            }
        }
        Insets insets = target.getInsets();
        tarsiz.width += insets.left + insets.right + hgap * 2;
        tarsiz.height += insets.top + insets.bottom + vgap * 2;
        return tarsiz;
    }

    /**
     * 将相关组件放置在垂直布局容器中
     * @param target 目标组件
     * @param x 起点横坐标
     * @param y 起点纵坐标
     * @param width 组件宽度
     * @param height 组件高度
     * @param first 首组件次序
     * @param last 末组件次序
     */
    private void placethem(Container target, int x, int y, int width, int height,
                           int first, int last) {
        int align = getAlignment();
        if (align == MIDDLE)
            y += height / 2;
        if (align == BOTTOM)
            y += height;
        
        for (int i = first; i < last; i++) {
            Component m = target.getComponent(i);
            Dimension md = m.getSize();
            if (m.isVisible()) {
                int px = x + (width - md.width) / 2;
                m.setLocation(px, y);
                y += vgap + md.height;
            }
        }
    }

    /**
     * 重写布局容器
     * @param target 需要修改的容器
     */
    @Override
    public void layoutContainer(Container target) {
        Insets insets = target.getInsets();
        int maxheight = target.getSize().height - (insets.top + insets.bottom + vgap * 2);
        int maxwidth = target.getSize().width - (insets.left + insets.right + hgap * 2);
        int numcomp = target.getComponentCount();
        int x = insets.left + hgap, y = 0;
        int colw = 0, start = 0;
        
        for (int i = 0; i < numcomp; i++) {
            Component m = target.getComponent(i);
            if (m.isVisible()) {
                Dimension d = m.getPreferredSize();
                // fit last component to remaining height
                if ((this.vfill) && (i == (numcomp - 1))) {
                    d.height = Math.max((maxheight - y), m.getPreferredSize().height);
                }
                
                // fit component size to container width
                if (this.hfill) {
                    m.setSize(maxwidth, d.height);
                    d.width = maxwidth;
                } else {
                    m.setSize(d.width, d.height);
                }
                
                if (y + d.height > maxheight) {
                    placethem(target, x, insets.top + vgap, colw, maxheight - y, start, i);
                    y = d.height;
                    x += hgap + colw;
                    colw = d.width;
                    start = i;
                } else {
                    if (y > 0)
                        y += vgap;
                    y += d.height;
                    colw = Math.max(colw, d.width);
                }
            }
        }
        placethem(target, x, insets.top + vgap, colw, maxheight - y, start, numcomp);
    }
}