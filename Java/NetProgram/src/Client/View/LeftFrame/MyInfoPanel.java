package Client.View.LeftFrame;

import Client.ClientCache;
import Client.View.MainFrame;
import Client.View.utils.AvatarUtil;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.GBC;
import Common.entity.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class MyInfoPanel extends ParentAvailablePanel {
    private static MyInfoPanel context;
    
    private JLabel avatar;
    private JLabel username;
    private JLabel menuIcon;
    private final User currentUser = ClientCache.currentUser;
    MainOperationPopupMenu mainOperationPopupMenu;
    private String currentUsername;
    
    public MyInfoPanel(JPanel parent) {
        super(parent);
        context = this;
        
        initComponents();
        setListeners();
        initView();
    }
    
    private void initComponents() {
        
        //GImage.setBorder(new SubtleSquareBorder(true));
        currentUsername = currentUser.getUsername();
        avatar = new JLabel();
        avatar.setIcon(new ImageIcon(AvatarUtil.createOrLoadUserAvatar(currentUser).getScaledInstance(50, 50, Image.SCALE_SMOOTH)));
        
        avatar.setPreferredSize(new Dimension(50, 50));
        avatar.setCursor(new Cursor(Cursor.HAND_CURSOR));
        
        username = new JLabel();
        username.setText(currentUsername);
        username.setFont(FontUtil.getDefaultFont(16));
        username.setForeground(Colors.FONT_WHITE);
        
        menuIcon = new JLabel();
        menuIcon.setIcon(new ImageIcon(getClass().getResource("/image/options.png")));
        menuIcon.setForeground(Colors.FONT_WHITE);
        menuIcon.setCursor(new Cursor(Cursor.HAND_CURSOR));
        mainOperationPopupMenu = new MainOperationPopupMenu();
        
    }


    private void setListeners()
    {
        menuIcon.addMouseListener(new MouseAdapter()
        {
            @Override
            public void mouseReleased(MouseEvent e)
            {
                if (e.getButton() == MouseEvent.BUTTON1)
                {
                    Component component = e.getComponent();
                    mainOperationPopupMenu.show(component, -112, 50);
                    super.mouseClicked(e);
                }

            }
        });

        avatar.addMouseListener(new MouseAdapter()
        {
            @Override
            public void mouseReleased(MouseEvent e)
            {
                if (e.getButton() == MouseEvent.BUTTON1)
                {
                    SystemConfigDialog dialog = new SystemConfigDialog(MainFrame.getContext(), true);
                    dialog.setVisible(true);
                    super.mouseClicked(e);
                }
            }
        });
    }

    
    private void initView() {
        this.setBackground(Colors.DARK);
        this.setLayout(new GridBagLayout());
        
        add(avatar, new GBC(0, 0).setFill(GBC.NONE).setWeight(2, 1));
        add(username, new GBC(1, 0).setFill(GBC.BOTH).setWeight(7, 1));
        add(menuIcon, new GBC(2, 0).setFill(GBC.BOTH).setWeight(1, 1));
    }
    
    public void reloadAvatar() {
        avatar.setIcon(new ImageIcon(AvatarUtil.createOrLoadUserAvatar(currentUser).getScaledInstance(50, 50, Image.SCALE_SMOOTH)));
//        avatar.revalidate();
        avatar.repaint();
    }
    
    public static MyInfoPanel getContext() {
        return context;
    }
}
