package Client.View.component.BubbleTextPanel;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Polygon;
import java.awt.RenderingHints;
import java.awt.geom.Area;
import java.awt.geom.RoundRectangle2D;
import javax.swing.JPanel;
public class RightArrowBubble extends JPanel {
    private static final long serialVersionUID = -5389178141802153305L;
    private int strokeThickness = 3;
    private int radius = 10;
    private int arrowSize = 2;
    private int padding = strokeThickness / 2;
    private int rightstart = 38;
    @Override
    protected void paintComponent(final Graphics g) {
        final Graphics2D g2d = (Graphics2D) g;
        g2d.setColor(new Color(152, 225, 101));
        int bottomLineY = getHeight() - strokeThickness-10;
        int width = getWidth() - arrowSize - (strokeThickness * 2)-180-rightstart;
        g2d.fillRect(padding+170, padding, width, bottomLineY);
        RoundRectangle2D.Double rect = new RoundRectangle2D.Double(padding+170, padding, width, bottomLineY,  radius, radius);
        Area area = new Area(rect);
        g2d.setRenderingHints(new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON));
        g2d.setStroke(new BasicStroke(strokeThickness));
        g2d.draw(area);
    }
}