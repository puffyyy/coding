package Client.View.component;

import Client.ClientCache;
import Client.View.RightFrame.RightPanel;
import Client.View.entity.GroupItem;
import Client.View.utils.Colors;

import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Comparator;

public class GroupScrollList extends JScrollPane {
    
    public JList<GroupItem> contentList;
    public DefaultListModel<GroupItem> jListModel;
    
    public GroupScrollList() {
        this.setBackground(Colors.ROOM_ITEM_GREY);
        this.setBorder(null);
        contentList = new JList<>();
        contentList.setFixedCellHeight(60);
        jListModel = new DefaultListModel<>();
        contentList.setCellRenderer(new GroupCellRender<>());
        this.setViewportView(contentList);
        this.verticalScrollBar.setUI(new MyScrollBarUI());
        this.setVerticalScrollBarPolicy(VERTICAL_SCROLLBAR_ALWAYS);
        this.setHorizontalScrollBarPolicy(HORIZONTAL_SCROLLBAR_NEVER);
        initData();
        addListener();
        refresh();
    }
    
    private void initData() {
        ClientCache.groupList.sort(new Comparator<GroupItem>() {
            public int compare(GroupItem p, GroupItem q) {
                return p.getTimestamp() < q.getTimestamp() ? -1 : 1;
            }
        });
        for (int i = ClientCache.groupList.size() - 1; i >= 0; i--) {
            GroupItem gi = ClientCache.groupList.get(i);
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
        //会将已选择的element的backgroundColor恢复默认
    }
    
}
