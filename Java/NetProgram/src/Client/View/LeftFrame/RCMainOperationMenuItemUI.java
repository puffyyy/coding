package Client.View.LeftFrame;

import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.component.RCBorder;

import javax.swing.*;
import javax.swing.plaf.basic.BasicMenuItemUI;
import java.awt.*;

public class RCMainOperationMenuItemUI extends BasicMenuItemUI {
    @Override
    public void installUI(JComponent c)
    {
        super.installUI(c);
        c.setPreferredSize(new Dimension(150, 40));
        c.setBackground(Colors.FONT_WHITE);
        c.setFont(FontUtil.getDefaultFont(13));
        c.setBorder(new RCBorder(RCBorder.BOTTOM, Colors.LIGHT_GRAY));
        selectionForeground = Colors.FONT_BLACK;
        selectionBackground = Colors.SCROLL_BAR_TRACK_LIGHT;
        
    }
    
    
    @Override
    protected void paintText(Graphics g, JMenuItem menuItem, Rectangle textRect, String text)
    {
        int x = (int) ((menuItem.getSize().getWidth() - textRect.width) / 2);
        
        g.setColor(Colors.FONT_BLACK);
        Rectangle newRect =  new Rectangle(x, textRect.y - 1 , textRect.width, textRect.height);
        super.paintText(g, menuItem, newRect, text);
    }

}
