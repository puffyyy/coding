package Client.View.RightFrame;

import Client.View.entity.GroupItem;
import Client.View.utils.Colors;
import Common.entity.User;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;

public class RightPanel extends JPanel {
    public static RightPanel context;
    
    private FuncTitlePanel funcTitlePanel;
    
    private ChatPanel chatPanel;
    private ContractorInfoPanel contractorInfoPanel;
    
    private JPanel contentPanel;
    private CardLayout cardLayout;
    
    public static final String MESSAGE = "MESSAGE";
    public static final String USER_INFO = "USER_INFO";

    /**
     * 聊天室整个右侧区域大Panel构造方法，包括内容、子组件、视图的初始化
     */
    public RightPanel() {
        context = this;
        initComponents();
        initView();
        
    }

    /**
     * 初始化子组件
     */
    private void initComponents() {
        this.setLayout(new GridBagLayout());
        cardLayout = new CardLayout();
        contentPanel = new JPanel();
        contentPanel.setLayout(cardLayout);
        
        funcTitlePanel = new FuncTitlePanel(this);
        chatPanel = new ChatPanel(this);
//        roomMembersPanel = new RoomMembersPanel(this);
        contractorInfoPanel = new ContractorInfoPanel(this);
        
        setBorder(new LineBorder(Colors.SCROLL_BAR_TRACK_LIGHT));
    }

    /**
     * 初始化视图
     */
    private void initView() {
        contentPanel.add(contractorInfoPanel, USER_INFO);
        contentPanel.add(chatPanel, MESSAGE);
        
        setBackground(Colors.FONT_WHITE);
        setLayout(new BorderLayout());
        setBorder(null);
//        add(roomMembersPanel, BorderLayout.EAST);
        add(funcTitlePanel, BorderLayout.NORTH);
        add(contentPanel, BorderLayout.CENTER);
        
    }

    /**
     * 展示子Panel
     * @param who 子组件主键
     */
    public void showPanel(String who) {
        cardLayout.show(contentPanel, who);
    }
    
    public ContractorInfoPanel getUserInfoPanel() {
        return contractorInfoPanel;
    }
    
    public static RightPanel getContext() {
        return context;
    }
    
    public void setUser(User u) {
        contractorInfoPanel.setUser(u);
        funcTitlePanel.updateRoomTitle(u.getUsername());
        showPanel(USER_INFO);
    }
    
    public void setRoom(GroupItem gi) {
        chatPanel.setCurGroup(gi);
        showPanel(MESSAGE);
    }
    
    public GroupItem getRoom() {
        return chatPanel.curGroup;
    }
    
    public FuncTitlePanel getTitlePanel() {
        return funcTitlePanel;
    }
    
}
