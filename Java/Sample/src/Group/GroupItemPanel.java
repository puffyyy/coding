package Group;

import utils.*;

import javax.swing.*;
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
        setPreferredSize(new Dimension(100, 64));
        setBackground(Colors.ROOM_ITEM_GREY);
        setBorder(new RCBorder(RCBorder.BOTTOM));
        setOpaque(true);

//        ImageIcon imageIcon = new ImageIcon(getClass().getResource("/image/avatar.jpg"));
//        imageIcon.setImage(imageIcon.getImage().getScaledInstance(40, 40, Image.SCALE_SMOOTH));
//        avatar.setIcon(imageIcon);
//        avatar.setIcon(new ImageIcon(utils.AvatarUtil.createOrLoadUserAvatar(imageFile).getScaledInstance(40, 40, Image.SCALE_SMOOTH)));
        roomName.setFont(FontUtil.getDefaultFont(14));
        roomName.setForeground(Colors.FONT_BLACK);
        
        brief.setForeground(Colors.ITEM_FONT_GREY);
        brief.setFont(FontUtil.getDefaultFont(12));
        
        nameBrief.setLayout(new BorderLayout());
        nameBrief.setOpaque(false);
        nameBrief.add(roomName, BorderLayout.NORTH);
        nameBrief.add(brief, BorderLayout.CENTER);
        
        time.setForeground(Colors.ITEM_FONT_GREY);
        time.setFont(FontUtil.getDefaultFont(12));
        
        unreadCount.setIcon(new ImageIcon(AvatarUtil.createOrLoadUserAvatar("count_bg").getScaledInstance(5, 5, Image.SCALE_SMOOTH)));
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
        add(avatar, new GBC(0, 0).setWeight(2, 1).setFill(GBC.BOTH).setInsets(0, 5, 0, 0));
        add(nameBrief, new GBC(1, 0).setWeight(100, 1).setFill(GBC.BOTH).setInsets(5, 5, 0, 0));
        add(timeUnread, new GBC(2, 0).setWeight(1, 1).setFill(GBC.BOTH).setInsets(5, 0, 0, 0));
    }
    
}
