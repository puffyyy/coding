package Client.View.RightFrame;

import Client.View.utils.Colors;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;

public class RightPanel extends JPanel {
    public static RightPanel context;
    private JPanel titlePanel;
    
    private JPanel chatPanel;
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
        cardLayout = new CardLayout();
        contentPanel = new JPanel();
        contentPanel.setLayout(cardLayout);

//        titlePanel = new TitlePanel(this);
//        chatPanel = new ChatPanel(this);
//        roomMembersPanel = new RoomMembersPanel(this);
        contractorInfoPanel = new ContractorInfoPanel(this);
        
        setBorder(new LineBorder(Colors.SCROLL_BAR_TRACK_LIGHT));
    }
    
    private void initView() {
        contentPanel.add(contractorInfoPanel, USER_INFO);
//        contentPanel.add(chatPanel, MESSAGE);
        
        this.setBackground(Colors.FONT_WHITE);
        this.setLayout(new BorderLayout());
//        add(titlePanel, BorderLayout.NORTH);
//        add(roomMembersPanel, BorderLayout.EAST);
        add(contentPanel, BorderLayout.CENTER);
    }
    
    public void showPanel(String who) {
        cardLayout.show(contentPanel, who);
    }

//    public RoomMembersPanel getRoomMembersPanel()
//    {
//        return roomMembersPanel;
//    }
    
    public ContractorInfoPanel getUserInfoPanel() {
        return contractorInfoPanel;
    }
    
    public static RightPanel getContext() {
        return context;
    }
}
