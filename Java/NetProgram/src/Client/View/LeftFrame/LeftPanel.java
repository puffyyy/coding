package Client.View.LeftFrame;

import Client.View.utils.Colors;
import Client.View.utils.GBC;

import javax.swing.*;
import java.awt.*;

public class LeftPanel extends JPanel {
    private MyInfoPanel myInfoPanel;
    //    private SearchPanel searchPanel;
    private TabOperationPanel mainOperationPanel;
    private ListPanel listPanel;
    
    public LeftPanel() {
        initComponents();
        initView();
    }
    
    private void initComponents() {
        myInfoPanel = new MyInfoPanel(this);
        mainOperationPanel = new TabOperationPanel(this);
        listPanel = new ListPanel(this);
        listPanel.setBackground(Colors.WINDOW_BACKGROUND);
    }
    
    private void initView() {
        this.setBackground(Colors.DARK);
        this.setLayout(new GridBagLayout());
        add(myInfoPanel, new GBC(0, 0).setAnchor(GBC.CENTER).setFill(GBC.BOTH).setInsets(0,0,10,0).setWeight(1, 7));
        add(mainOperationPanel, new GBC(0, 2).setAnchor(GBC.CENTER).setFill(GBC.BOTH).setWeight(1, 1));
        add(listPanel, new GBC(0, 3).setAnchor(GBC.CENTER).setFill(GBC.BOTH).setWeight(1, 60));
        
    }
    
    public ListPanel getListPanel() {
        return this.listPanel;
    }
    
}
