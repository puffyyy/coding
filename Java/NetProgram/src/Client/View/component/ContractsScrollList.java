package Client.View.component;

import Client.ClientCache;
import Client.View.RightFrame.RightPanel;
import Client.View.utils.Colors;
import Common.entity.User;

import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Comparator;

//image + text
public class ContractsScrollList extends JScrollPane {
    public JList<User> contentList;
    public DefaultListModel<User> listModel;
    
    public ContractsScrollList() {
        this.contentList = new JList<>();
        this.listModel = new DefaultListModel<>();
        this.setBorder(null);
        this.verticalScrollBar.setUI(new MyScrollBarUI());
        this.setVerticalScrollBarPolicy(VERTICAL_SCROLLBAR_ALWAYS);
        this.setHorizontalScrollBarPolicy(HORIZONTAL_SCROLLBAR_NEVER);
        initData();
        initView();
        initComponents();
        addListener();
    }
    
    private void initData() {
        ClientCache.friendUserList.sort(new Comparator<User>() {
            @Override
            public int compare(User o1, User o2) {
                return o1.getUsername().compareTo(o2.getUsername());
            }
        });
        for (User s : ClientCache.friendUserList) {
            listModel.addElement(s);
        }
    }
    
    private void initComponents() {
        contentList.setModel(listModel);
        contentList.setCellRenderer(new ImageTextCellRender());
    }
    
    private void initView() {
        contentList.setFixedCellHeight(60);
//        contentList.setUI(new BasicListUI());
        
        setBackground(Colors.WINDOW_BACKGROUND);
        setViewportView(contentList);
        setVisible(true);
    }
    
    private void addListener() {
        contentList.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if (e.getClickCount() == 2) {
                    RightPanel.getContext().setUser(contentList.getSelectedValue());
                }

/*
                javax.swing.Timer mouseTimer = new javax.swing.Timer(350, evt -> {});
                if (e.getClickCount() == 1) {
                    mouseTimer.restart();
                } else if (e.getClickCount() == 2 && mouseTimer.isRunning()) {
                    mouseTimer.stop();
                    System.out.println("");
                }
*/
            }
        });
    }
    
    public User getSelectItem() {
        return contentList.getSelectedValue();
    }
    
    public Integer getSelectIndex() {
        return contentList.getSelectedIndex();
    }
    
    public void refresh() {
        listModel.clear();
        initData();
        contentList.setModel(listModel);
    }
}
