package Client.View.utils.component;

import Client.View.utils.Colors;
import Common.entity.User;

import javax.swing.*;
import javax.swing.plaf.basic.BasicListUI;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

//image + text
public class ContractsScrollList extends JScrollPane {
    public JList<User> contentList;
    public DefaultListModel<User> listModel;
    public ArrayList<User> usersList;
    
    public ContractsScrollList(ArrayList<User> users) {
        this.contentList = new JList<>();
        this.listModel = new DefaultListModel<>();
        usersList = users;
        initView();
        initComponents();
        addListener();
    }
    
    private void initComponents() {
        for (User s : usersList) {
            listModel.addElement(s);
        }
        contentList.setModel(listModel);
        contentList.setCellRenderer(new ImageTextCellRender());
    }
    
    private void initView() {
        contentList.setFixedCellHeight(50);
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
                    System.out.println(contentList.getSelectedIndex() + " click 2");
                    //TODO open new room
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
}
