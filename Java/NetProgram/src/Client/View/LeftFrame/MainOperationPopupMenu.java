package Client.View.LeftFrame;

import Client.View.MainFrame;
import Client.View.utils.Colors;
import org.jb2011.lnf.beautyeye.ch9_menu.BEMenuItemUI;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainOperationPopupMenu extends JPopupMenu
{
    public MainOperationPopupMenu()
    {
        initMenuItem();
    }

    private void initMenuItem()
    {
        JMenuItem item1 = new JMenuItem("创建群聊");
        JMenuItem item2 = new JMenuItem("设置");
        JMenuItem addFriend = new JMenuItem("添加好友");
        item1.setUI(new RCMainOperationMenuItemUI());
        item1.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                CreateGroupDialog dialog = new CreateGroupDialog(MainFrame.getContext(), true);
                dialog.setVisible(true);
                //TODO create group
            }
        });
        ImageIcon icon1 = new ImageIcon(getClass().getResource("/image/chat.png"));
        icon1.setImage(icon1.getImage().getScaledInstance(20, 20, Image.SCALE_SMOOTH));
        item1.setIcon(icon1);
        item1.setIconTextGap(5);

        item2.setUI(new RCMainOperationMenuItemUI());
        item2.addActionListener(new AbstractAction()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                SystemConfigDialog dialog = new SystemConfigDialog(MainFrame.getContext(), true);
                dialog.setVisible(true);
            }
        });
        ImageIcon icon2 = new ImageIcon(getClass().getResource("/image/setting.png"));
        icon2.setImage(icon2.getImage().getScaledInstance(20, 20, Image.SCALE_SMOOTH));
        item2.setIcon(icon2);
        item2.setIconTextGap(5);


        addFriend.setUI(new RCMainOperationMenuItemUI());
        ImageIcon icon3 = new ImageIcon(getClass().getResource("/image/add_friend.png"));
        icon3.setImage(icon3.getImage().getScaledInstance(20, 20, Image.SCALE_SMOOTH));
        addFriend.setIcon(icon3);
        addFriend.setIconTextGap(5);
        addFriend.addActionListener(new AbstractAction()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                AddFriendDialog dialog = new AddFriendDialog(MainFrame.getContext(), true);
                dialog.setVisible(true);
            }
        });
        
        this.add(item1);
        this.add(addFriend);
        this.add(item2);

        setBorder(new LineBorder(Colors.SCROLL_BAR_TRACK_LIGHT));
        setBackground(Colors.FONT_WHITE);
    }
    
}
