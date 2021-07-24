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

    /**
     * 滚动列表构造方法
     */
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

    /**
     * 初始化数据
     */
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

    /**
     * 初始化子组件
     */
    private void initComponents() {
        contentList.setModel(listModel);
        contentList.setCellRenderer(new ImageTextCellRender());
    }

    /**
     * 初始化视图
     */
    private void initView() {
        contentList.setFixedCellHeight(60);
//        contentList.setUI(new BasicListUI());
        
        setBackground(Colors.WINDOW_BACKGROUND);
        setViewportView(contentList);
        setVisible(true);
    }

    /**
     * 设置滚动列表部分的监听器
     */
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

    /**
     * 刷新滚动列表
     */
    public void refresh() {
        listModel.clear();
        initData();
        contentList.setModel(listModel);
    }
}
