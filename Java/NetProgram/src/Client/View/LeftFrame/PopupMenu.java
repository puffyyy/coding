package Client.View.LeftFrame;

import Client.View.MainFrame;
import Client.View.component.RCBorder;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;

import javax.swing.*;
import javax.swing.border.LineBorder;
import javax.swing.plaf.basic.BasicMenuItemUI;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class PopupMenu extends JPopupMenu {
    public PopupMenu() {
        initMenuItem();
    }
    
    private void initMenuItem() {
        JMenuItem item1 = new JMenuItem("创建群聊");
        JMenuItem item2 = new JMenuItem("设置");
        JMenuItem addFriend = new JMenuItem("添加好友");
        JMenuItem addFriendResult = new JMenuItem("新的朋友");
        item1.setUI(new MenuItemUI());
        item1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                CreateGroupDialog dialog = new CreateGroupDialog(MainFrame.getContext(), true);
                dialog.setVisible(true);
            }
        });
        ImageIcon icon1 = new ImageIcon(getClass().getResource("/image/chat.png"));
        icon1.setImage(icon1.getImage().getScaledInstance(20, 20, Image.SCALE_SMOOTH));
        item1.setIcon(icon1);
        item1.setIconTextGap(5);
        
        item2.setUI(new MenuItemUI());
        item2.addActionListener(new AbstractAction() {
            private static final long serialVersionUID = 3466310698845962401L;
            
            @Override
            public void actionPerformed(ActionEvent e) {
                UserConfigDialog dialog = new UserConfigDialog(MainFrame.getContext(), true);
                dialog.setVisible(true);
            }
        });
        ImageIcon icon2 = new ImageIcon(getClass().getResource("/image/setting.png"));
        icon2.setImage(icon2.getImage().getScaledInstance(20, 20, Image.SCALE_SMOOTH));
        item2.setIcon(icon2);
        item2.setIconTextGap(5);
        
        addFriend.setUI(new MenuItemUI());
        ImageIcon icon3 = new ImageIcon(getClass().getResource("/image/add_friend.png"));
        icon3.setImage(icon3.getImage().getScaledInstance(20, 20, Image.SCALE_SMOOTH));
        addFriend.setIcon(icon3);
        addFriend.setIconTextGap(5);
        addFriend.addActionListener(new AbstractAction() {
            private static final long serialVersionUID = 404598044630505768L;
            
            @Override
            public void actionPerformed(ActionEvent e) {
                AddFriendDialog dialog = new AddFriendDialog(MainFrame.getContext(), true);
                dialog.setVisible(true);
            }
        });
        
        addFriendResult.setUI(new MenuItemUI());
        ImageIcon icon4 = new ImageIcon(getClass().getResource("/image/add_member.png"));
        icon4.setImage(icon4.getImage().getScaledInstance(20, 20, Image.SCALE_SMOOTH));
        addFriendResult.setIcon(icon4);
        addFriendResult.setIconTextGap(5);
        addFriendResult.addActionListener(new AbstractAction() {
            private static final long serialVersionUID = 3741166353918726174L;
            
            @Override
            public void actionPerformed(ActionEvent e) {
                NoticeDialog dialog = new NoticeDialog(MainFrame.getContext(), true);
                dialog.setVisible(true);
            }
        });
        
        this.add(addFriend);
        this.add(addFriendResult);
        this.add(item1);
        this.add(item2);
        
        setBorder(new LineBorder(Colors.SCROLL_BAR_TRACK_LIGHT));
        setBackground(Colors.FONT_WHITE);
    }
    
}

class MenuItemUI extends BasicMenuItemUI {
    @Override
    public void installUI(JComponent c) {
        super.installUI(c);
        c.setPreferredSize(new Dimension(150, 40));
        c.setBackground(Colors.FONT_WHITE);
        c.setFont(FontUtil.getDefaultFont(13));
        c.setBorder(new RCBorder(RCBorder.BOTTOM, Colors.LIGHT_GRAY));
        selectionForeground = Colors.FONT_BLACK;
        selectionBackground = Colors.SCROLL_BAR_TRACK_LIGHT;
    }
    
    @Override
    protected void paintText(Graphics g, JMenuItem menuItem, Rectangle textRect, String text) {
        int x = (int) ((menuItem.getSize().getWidth() - textRect.width) / 2);
        g.setColor(Colors.FONT_BLACK);
        Rectangle newRect = new Rectangle(x, textRect.y - 1, textRect.width, textRect.height);
        super.paintText(g, menuItem, newRect, text);
    }
    
}
