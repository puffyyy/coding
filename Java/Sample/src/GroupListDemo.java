import Group.GroupCellRenderPanel;
import Group.GroupItem;

import javax.swing.*;
import java.awt.*;
import java.util.Date;

public class GroupListDemo extends JFrame {
    
    private static final long serialVersionUID = 1L;
    
    public GroupListDemo() {
        JList<GroupItem> list = new JList<>();
        DefaultListModel<GroupItem> listModel = new DefaultListModel<>();
        
        listModel.addElement(new GroupItem("1", "董强", "想吃一顿好的，去哪里吃饭干呢，能和一升可乐，大事不妙", 1, new Date().getTime(),"u"));
        list.setModel(listModel);
        list.setCellRenderer(new GroupCellRenderPanel<>());
        
        JScrollPane scrollPane = new JScrollPane(list);
        getContentPane().add(scrollPane, BorderLayout.CENTER);
        getContentPane().add(new JLabel("chatee"), BorderLayout.NORTH);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(900, 350, 50, 300);
        
    }
    
    public static void main(String[] args) {
        new GroupListDemo().setVisible(true);
    }
}
