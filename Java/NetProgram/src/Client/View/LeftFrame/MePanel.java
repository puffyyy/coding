package Client.View.LeftFrame;

import Client.ClientCache;
import Client.View.MainFrame;
import Client.View.utils.AvatarUtil;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.GBC;
import Client.View.utils.component.RCButton;
import Common.entity.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class MePanel extends JPanel {
    private JPanel contentPanel;
    private JLabel imageLabel;
    private JLabel nameLabel;
    private RCButton button;
    private final User currentUser;
    
    public MePanel() {
        currentUser = ClientCache.currentUser;
        initComponents();
        initView();
        setListeners();
    }
    
    private void initComponents() {
        contentPanel = new JPanel();
        contentPanel.setLayout(new BorderLayout(0, 15));
        
        imageLabel = new JLabel();
        ImageIcon icon = new ImageIcon(AvatarUtil.createOrLoadUserAvatar(currentUser).getScaledInstance(100, 100, Image.SCALE_SMOOTH));
        imageLabel.setIcon(icon);
        
        nameLabel = new JLabel();
//        nameLabel.setBorder(new RCBorder());
        nameLabel.setText(currentUser.getUsername());
        nameLabel.setFont(FontUtil.getDefaultFont(20));
        
        button = new RCButton("退出登录", Colors.MAIN_COLOR, Colors.MAIN_COLOR_DARKER, Colors.MAIN_COLOR_DARKER);
        button.setBackground(Colors.PROGRESS_BAR_START);
        button.setPreferredSize(new Dimension(200, 35));
        button.setFont(FontUtil.getDefaultFont(16));
        
    }
    
    private void initView() {
        this.setLayout(new GridBagLayout());
        
        JPanel avatarNamePanel = new JPanel();
        JPanel usernamePanel = new JPanel();
        avatarNamePanel.add(imageLabel);
        usernamePanel.add(nameLabel);
        
        contentPanel.add(avatarNamePanel, BorderLayout.NORTH);
        contentPanel.add(usernamePanel,BorderLayout.CENTER);
        contentPanel.add(button, BorderLayout.SOUTH);
        
        add(contentPanel, new GBC(0, 0).setWeight(1, 1).setAnchor(GBC.CENTER).setInsets(0, 0, 200, 0));//250
    }
    
    private void setListeners() {
        button.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                int ret = JOptionPane.showConfirmDialog(MainFrame.getContext(), "确认退出登录？", "确认退出", JOptionPane.YES_NO_OPTION);
                if (ret == JOptionPane.YES_OPTION) {
                    // TODO: send quit request
                    MainFrame.getContext().dispose();
                    System.exit(0);
                }
                
                super.mouseClicked(e);
            }
        });
    }
    
    public static void main(String[] args) {
        JFrame jf = new JFrame();
        JPanel avatarNamePanel = new JPanel();
        JLabel imageLabel = new JLabel();
        imageLabel.setSize(100,100);
        imageLabel.setText("asdfadf");
        JLabel nameLabel = new JLabel("asd");
        JPanel name = new JPanel();
        nameLabel.setSize(50,20);
        name .add(nameLabel);
        avatarNamePanel.setLayout(new BorderLayout(15, 0));
        avatarNamePanel.add(imageLabel, BorderLayout.NORTH);
        avatarNamePanel.add(name, BorderLayout.CENTER);
        jf.add(avatarNamePanel);
        jf.pack();
        jf.setVisible(true);
        
    }
    
}
