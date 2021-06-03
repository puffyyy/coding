package Client.View.component.BubbleTextPanel;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Area;
import java.awt.geom.RoundRectangle2D;

public class LeftArrowBubble extends JPanel {
    private static final long serialVersionUID = -5389178141802153305L;
    private final int radius = 10;
    private final int arrowSize = 2;
    private final int strokeThickness = 2;
    private final int padding = strokeThickness / 2;
    private final int leftStart = 50;

    @Override
    protected void paintComponent(final Graphics g) {
        final Graphics2D g2d = (Graphics2D) g;
        g2d.setColor(new Color(182, 186, 208));
        int x = padding + strokeThickness + arrowSize + leftStart;
        int width = getWidth() - arrowSize - (strokeThickness * 2) -240;
        int bottomLineY = getHeight() - strokeThickness-10;
        
        g2d.fillRect(x, padding, width, bottomLineY);
        g2d.setRenderingHints(new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON));
        g2d.setStroke(new BasicStroke(strokeThickness));
        RoundRectangle2D.Double rect = new RoundRectangle2D.Double(x, padding, width, bottomLineY, radius, radius);
        Area area = new Area(rect);
        g2d.draw(area);
    }
    
}