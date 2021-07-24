package Client.View.LeftFrame;

import Client.View.utils.Colors;
import Client.View.utils.GBC;

import javax.swing.*;
import java.awt.*;

public class LeftPanel extends JPanel {
    private MyInfoPanel myInfoPanel;
    private TabPanel mainOperationPanel;
    private ListPanel listPanel;

    /**
     * 聊天室左侧Panel的构造方法，调用了子组件和视图的初始化
     */
    public LeftPanel() {
        initComponents();
        initView();
    }

    /**
     * 初始化子组件
     */
    private void initComponents() {
        myInfoPanel = new MyInfoPanel(this);
        mainOperationPanel = new TabPanel(this);
        listPanel = new ListPanel(this);
        listPanel.setBackground(Colors.WINDOW_BACKGROUND);
    }

    /**
     * 初始化视图
     */
    private void initView() {
        this.setBackground(Colors.DARK);
        this.setLayout(new GridBagLayout());
        add(myInfoPanel, new GBC(0, 0).setAnchor(GBC.CENTER).setFill(GBC.BOTH).setInsets(0, 0, 10, 0).setWeight(1, 7));
        add(mainOperationPanel, new GBC(0, 2).setAnchor(GBC.CENTER).setFill(GBC.BOTH).setWeight(1, 1));
        add(listPanel, new GBC(0, 3).setAnchor(GBC.CENTER).setFill(GBC.BOTH).setWeight(1, 60));
    }

    /**
     * 获取消息列表
     * @return 消息列表
     */
    public ListPanel getListPanel() {
        return this.listPanel;
    }
    
}
