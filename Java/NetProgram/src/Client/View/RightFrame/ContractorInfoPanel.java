package Client.View.RightFrame;

import Client.ClientCache;
import Client.View.LeftFrame.AvailablePanel;
import Client.View.LeftFrame.ListPanel;
import Client.View.component.RCButton;
import Client.View.entity.GroupItem;
import Client.View.utils.AvatarUtil;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.GBC;
import Common.entity.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import static Client.View.LeftFrame.ListPanel.CONTACTS;

public class ContractorInfoPanel extends AvailablePanel {
    
    private JPanel contentPanel;
    private JLabel imageLabel;
    private JLabel nameLabel;
    private JLabel phoneLabel;
    private RCButton button;
    
    private User currUser;
    
    public ContractorInfoPanel(JPanel parent) {
        super(parent);
        initComponents();
        initView();
        setListeners();
    }
    
    private void initComponents() {
        setBackground(Colors.WINDOW_BACKGROUND);
        contentPanel = new JPanel();
        contentPanel.setBackground(Colors.WINDOW_BACKGROUND);
        contentPanel.setLayout(new BorderLayout(0, 35));
        imageLabel = new JLabel();
        nameLabel = new JLabel();
        nameLabel.setPreferredSize(new Dimension(100, 35));
        nameLabel.setFont(FontUtil.getDefaultFont(25));
        nameLabel.setHorizontalAlignment(SwingConstants.CENTER);
        phoneLabel = new JLabel();
        phoneLabel.setFont(FontUtil.getDefaultFont(18));
        button = new RCButton("发消息", Colors.MAIN_COLOR, Colors.MAIN_COLOR_DARKER, Colors.MAIN_COLOR_DARKER);
        button.setBackground(Colors.PROGRESS_BAR_START);
        button.setPreferredSize(new Dimension(200, 40));
        button.setFont(FontUtil.getDefaultFont(16));
        button.setBorder(null);
        button.setOpaque(false);
        button.setVisible(false);
    }
    
    private void initView() {
        this.setLayout(new GridBagLayout());
        
        JPanel avatarPanel = new JPanel(new GridBagLayout());
        avatarPanel.setOpaque(false);
        avatarPanel.add(imageLabel, new GBC(0, 0).setWeight(2, 2).setAnchor(GBC.CENTER).setInsets(10, 0, 40, 0));
        avatarPanel.add(nameLabel, new GBC(0, 1).setWeight(1, 1).setAnchor(GBC.CENTER));
        
        JPanel userPanel = new JPanel();
        userPanel.setOpaque(false);
        userPanel.add(phoneLabel, BorderLayout.SOUTH);
        
        contentPanel.add(avatarPanel, BorderLayout.NORTH);
        contentPanel.add(userPanel, BorderLayout.CENTER);
        contentPanel.add(button, BorderLayout.SOUTH);
        
        add(contentPanel, new GBC(0, 0).setWeight(1, 1).setAnchor(GBC.CENTER).setInsets(100, 0, 130, 0));
    }
    
    public void setUser(User user) {
        currUser = user;
        nameLabel.setText(currUser.getUsername());
        ImageIcon icon = new ImageIcon(AvatarUtil.createOrLoadUserAvatar(currUser).getScaledInstance(100, 100, Image.SCALE_SMOOTH));
        imageLabel.setIcon(icon);
        phoneLabel.setText("TEL: " + currUser.getPhoneNum());
        Color color = Colors.randColor(currUser.getUid());
        setBackground(color);
        contentPanel.setBackground(color);
        button.setVisible(true);
    }
    
    private void setListeners() {
        button.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                openOrCreateDirectChat();
                ListPanel.getContext().showPanel(CONTACTS);
            }
        });
    }
    
    private void openOrCreateDirectChat() {
        Long userId = currUser.getUid();
        GroupItem gi = ClientCache.contractorGroupMap.get(userId);
        if (gi != null) {
            RightPanel.getContext().setRoom(gi);
        } else {
            //send req
        }
    }
    
}
