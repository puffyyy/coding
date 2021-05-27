package Client.View.LeftFrame;

import Client.ClientCache;
import Client.View.utils.Colors;
import Client.View.utils.component.ContractsScrollList;
import Client.View.utils.component.GroupScrollList;

import javax.swing.*;
import java.awt.*;

public class ListPanel extends ParentAvailablePanel {
    private static ListPanel context;
    private GroupScrollList roomsPanel;
    private ContractsScrollList contactsPanel;
    
    public static final String CHAT = "CHAT";
    public static final String CONTACTS = "CONTACTS";
    
    private final CardLayout cardLayout = new CardLayout();
    
    public ListPanel(JPanel parent) {
        super(parent);
        context = this;
        
        initComponents();
        initView();
    }
    
    private void initComponents() {
        roomsPanel = new GroupScrollList();
        contactsPanel = new ContractsScrollList();
    }
    
    private void initView() {
        this.setLayout(cardLayout);
        setBackground(Colors.WINDOW_BACKGROUND);
        add(roomsPanel, CHAT);
        add(contactsPanel, CONTACTS);
    }

    public void showPanel(String who) {
        cardLayout.show(this, who);
    }
    public void refreshRooms(){
        roomsPanel.refresh();
    }
    public void refreshContracts(){
        contactsPanel.refresh();
    }
    public static ListPanel getContext() {
        return context;
    }
    
}
