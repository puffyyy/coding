package Client.View.RightFrame;

import Client.ClientCache;
import Client.View.LeftFrame.AvailablePanel;
import Client.View.LeftFrame.ListPanel;
import Client.View.component.MyScrollBarUI;
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
    private MyScrollBarUI.MyButton button;
    
    private User currUser;

    /**
     * 联系或信息Panel构造方法，包括子组件、视图的初始化和监听器的设置
     * @param parent 父组件
     */
    public ContractorInfoPanel(JPanel parent) {
        super(parent);
        initComponents();
        initView();
        setListeners();
    }

    /**
     * 初始化子组件
     */
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
        button = new MyScrollBarUI.MyButton("发消息", Colors.MAIN_COLOR, Colors.MAIN_COLOR_DARKER, Colors.MAIN_COLOR_DARKER);
        button.setBackground(Colors.PROGRESS_BAR_START);
        button.setPreferredSize(new Dimension(200, 40));
        button.setFont(FontUtil.getDefaultFont(16));
        button.setBorder(null);
        button.setOpaque(false);
        button.setVisible(false);
    }

    /**
     * 初始化视图
     */
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

    /**
     * 填充用户信息
     * @param user 使用用户
     */
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

    /**
     * 设置监听器
     */
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

    /**
     * 打开或新建一个聊天
     */
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
