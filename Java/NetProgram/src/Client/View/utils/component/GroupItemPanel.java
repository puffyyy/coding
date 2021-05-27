package Client.View.utils.component;

import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.GBC;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;

public class GroupItemPanel extends JPanel {
    public JLabel avatar = new JLabel();
    public JLabel roomName = new JLabel();
    public JLabel brief = new JLabel();
    public JLabel time = new JLabel();
    public JLabel unreadCount = new JLabel();
    
    public JPanel nameBrief = new JPanel();
    public JPanel timeUnread = new JPanel();
    
    public GroupItemPanel() {
        initComponents();
        initView();
    }
    
    private void initComponents() {
//        setPreferredSize(new Dimension(100, 64));
        setBackground(Colors.ROOM_ITEM_GREY);
        setOpaque(true);
        this.setBorder(new EmptyBorder(10, 10, 10, 5));
        roomName.setFont(FontUtil.getDefaultFont(14));
        roomName.setForeground(Colors.FONT_BLACK);
        
        brief.setForeground(Colors.ITEM_FONT_GREY);
        brief.setFont(FontUtil.getDefaultFont(12));
        
        nameBrief.setLayout(new BorderLayout());
        nameBrief.setOpaque(false);
        nameBrief.add(roomName, BorderLayout.NORTH);
        nameBrief.add(brief, BorderLayout.SOUTH);
        
        time.setForeground(Colors.ITEM_FONT_GREY);
        time.setFont(FontUtil.getDefaultFont(12));
        unreadCount.setIcon(new ImageIcon((new ImageIcon(getClass().getResource("/image/count_bg.png")).getImage()
                .getScaledInstance(5, 5, Image.SCALE_SMOOTH))));
        unreadCount.setFont(FontUtil.getDefaultFont(12));
        unreadCount.setPreferredSize(new Dimension(10, 10));
        unreadCount.setForeground(Colors.FONT_WHITE);
        unreadCount.setHorizontalTextPosition(SwingConstants.CENTER);
        unreadCount.setHorizontalAlignment(SwingConstants.CENTER);
        unreadCount.setVerticalAlignment(SwingConstants.CENTER);
        unreadCount.setVerticalTextPosition(SwingConstants.CENTER);
        
        timeUnread = new JPanel();
        timeUnread.setLayout(new BorderLayout());
        timeUnread.setOpaque(false);
        timeUnread.add(time, BorderLayout.NORTH);
        timeUnread.add(unreadCount, BorderLayout.CENTER);
        
    }
    
    private void initView() {
        setLayout(new GridBagLayout());
        add(avatar, new GBC(0, 0).setWeight(2, 1).setFill(GBC.BOTH).setInsets(0, 5, 0, 5));
        add(nameBrief, new GBC(1, 0).setWeight(100, 1).setFill(GBC.BOTH).setInsets(0, 5, 0, 0));
        add(timeUnread, new GBC(2, 0).setWeight(1, 1).setFill(GBC.BOTH).setInsets(0, 0, 0, 0));
    }
    
}
