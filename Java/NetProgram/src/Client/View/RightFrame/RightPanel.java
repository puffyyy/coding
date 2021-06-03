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
    
    public RightPanel() {
        context = this;
        initComponents();
        initView();
        
    }
    
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
