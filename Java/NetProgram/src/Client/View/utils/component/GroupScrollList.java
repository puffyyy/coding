package Client.View.utils.component;

import Client.ClientCache;
import Client.View.RightFrame.RightPanel;
import Client.View.entity.GroupItem;
import Client.View.utils.Colors;
import Common.entity.Group;

import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class GroupScrollList extends JScrollPane {
    
    public JList<GroupItem> contentList;
    public DefaultListModel<GroupItem> jListModel;
    
    public GroupScrollList() {
        this.setBackground(Colors.WINDOW_BACKGROUND);
        contentList = new JList<>();
        contentList.setFixedCellHeight(60);
        jListModel = new DefaultListModel<>();
        contentList.setCellRenderer(new GroupCellRender<>());
        this.setViewportView(contentList);
        initData();
        addListener();
        refresh();
    }
    
    private void initData() {
        for (Group g : ClientCache.groupList) {
            GroupItem gi = new GroupItem(g);
            jListModel.addElement(gi);
        }
    }
    
    private void addListener() {
        contentList.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if (e.getClickCount() == 2) {
                    RightPanel.getContext().setRoom(contentList.getSelectedValue());
                }
            }
        });
    }
    
    public void refresh() {
        jListModel.clear();
        initData();
        contentList.setModel(jListModel);
        
    }
    
}
