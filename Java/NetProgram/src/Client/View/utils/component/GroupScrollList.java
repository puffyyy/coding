package Client.View.utils.component;

import Client.ClientCache;
import Client.View.entity.GroupItem;
import Client.View.utils.Colors;
import Common.entity.Group;
import Common.entity.User;

import javax.swing.*;

public class GroupScrollList extends JScrollPane {
    
    public JList<GroupItem> contentList;
    public DefaultListModel<GroupItem> jListModel;
    
    public GroupScrollList() {
        this.setBackground(Colors.WINDOW_BACKGROUND);
        contentList = new JList<>();
        contentList.setFixedCellHeight(50);
        jListModel = new DefaultListModel<>();
        contentList.setCellRenderer(new GroupCellRender<>());
        this.setViewportView(contentList);
        initData();
        refresh();
    }
    
    public void initData() {
        for (Group g : ClientCache.groupList) {
            GroupItem gi = new GroupItem(g);
            jListModel.addElement(gi);
        }
    }
    
    public void refresh() {
        //TODO
        contentList.setModel(jListModel);
        
    }
    
}
