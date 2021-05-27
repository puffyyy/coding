package Client.View.RightFrame;

import Client.View.LeftFrame.ParentAvailablePanel;
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

public class ContractorInfoPanel extends ParentAvailablePanel {
    
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
        
        contentPanel = new JPanel();
        contentPanel.setLayout(new BorderLayout(0, 35));
        imageLabel = new JLabel();
        nameLabel = new JLabel();
        nameLabel.setPreferredSize(new Dimension(50, 20));
        nameLabel.setFont(FontUtil.getDefaultFont(20));
        phoneLabel = new JLabel();
        phoneLabel.setFont(FontUtil.getDefaultFont(18));
        button = new RCButton("发消息", Colors.MAIN_COLOR, Colors.MAIN_COLOR_DARKER, Colors.MAIN_COLOR_DARKER);
        button.setBackground(Colors.PROGRESS_BAR_START);
        button.setPreferredSize(new Dimension(200, 40));
        button.setFont(FontUtil.getDefaultFont(16));
        
    }
    
    private void initView() {
        this.setLayout(new GridBagLayout());
        
        JPanel avatarPanel = new JPanel(new GridBagLayout());
        
        avatarPanel.add(nameLabel, new GBC(0, 0).setWeight(1, 1).setAnchor(GBC.NORTHEAST).setInsets(0, 15, 0, 50));
        avatarPanel.add(new JLabel(), new GBC(2, 0).setWeight(10, 10).setAnchor(GBC.CENTER).setInsets(0, 15, 0, 15));
        avatarPanel.add(imageLabel, new GBC(4, 0).setWeight(2, 2).setAnchor(GBC.WEST).setInsets(0, 15, 0, 15));
        JPanel userPanel = new JPanel();
        
        userPanel.add(phoneLabel, BorderLayout.SOUTH);
        contentPanel.add(avatarPanel, BorderLayout.NORTH);
        contentPanel.add(userPanel, BorderLayout.CENTER);
        contentPanel.add(button, BorderLayout.SOUTH);
        
        add(contentPanel, new GBC(0, 0).setWeight(1, 1).setAnchor(GBC.CENTER).setInsets(100, 0, 150, 0));
    }
    
    public void setUser(User user) {
        currUser = user;
        nameLabel.setText(currUser.getUsername());
        ImageIcon icon = new ImageIcon(AvatarUtil.createOrLoadUserAvatar(currUser).getScaledInstance(100, 100, Image.SCALE_SMOOTH));
        imageLabel.setIcon(icon);
        phoneLabel.setText("TEL: " + currUser.getPhoneNum());
    }
    
    private void setListeners() {
        button.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                
                openOrCreateDirectChat();
                super.mouseClicked(e);
            }
        });
    }
    
    private void openOrCreateDirectChat() {
//        String userId = user.getUserId();
//
//        // 房间已存在，直接打开，否则发送请求创建房间
//        if (room != null) {
//            ChatPanel.getContext().enterRoom(room.getRoomId());
//        } else {
//            createDirectChat(user.getName());
//        }
    }
    
    public void createDirectChat(String username) {
        JOptionPane.showMessageDialog(MainFrame.getContext(), "发起聊天", "发起聊天", JOptionPane.INFORMATION_MESSAGE);
    }
    
    public static void main(String[] args) {
        JFrame j = new JFrame();
        JPanel jf = new JPanel();
        j.add(jf);
        
        ContractorInfoPanel co = new ContractorInfoPanel(jf);
        jf.add(co);
        co.setUser(new User(1L, "1", "1", '1', "1300000000", "./cache/image/1.png"));
        j.pack();
        j.setVisible(true);
    }
    
}
