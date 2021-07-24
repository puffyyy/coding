package Client.View.LeftFrame;

import Client.View.component.ContractsScrollList;
import Client.View.component.GroupScrollList;
import Client.View.utils.Colors;

import javax.swing.*;
import java.awt.*;

public class ListPanel extends AvailablePanel {
    private static ListPanel context;
    private GroupScrollList roomsPanel;
    private ContractsScrollList contactsPanel;
    
    public static final String CHAT = "CHAT";
    public static final String CONTACTS = "CONTACTS";
    
    private final CardLayout cardLayout = new CardLayout();

    /**
     * 列表Panel构造方法
     * @param parent 父Panel
     */
    public ListPanel(JPanel parent) {
        super(parent);
        context = this;
        
        initComponents();
        initView();
        
    }

    /**
     * 初始化子组件
     */
    private void initComponents() {
        roomsPanel = new GroupScrollList();
        contactsPanel = new ContractsScrollList();
    }

    /**
     * 初始化视图
     */
    private void initView() {
        this.setLayout(cardLayout);
        setBackground(Colors.WINDOW_BACKGROUND);
        add(roomsPanel, CHAT);
        add(contactsPanel, CONTACTS);
    }

    /**
     * 显示卡片视图
     * @param who 消息字符串
     */
    public void showPanel(String who) {
        cardLayout.show(this, who);
    }

    /**
     * 刷新内容
     */
    public void refreshRooms() {
        roomsPanel.refresh();
    }

    /**
     * 刷新相关联系
     */
    public void refreshContracts() {
        contactsPanel.refresh();
    }

    public static ListPanel getContext() {
        return context;
    }
    
}
