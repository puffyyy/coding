package Client.View.LeftFrame;

import javax.swing.*;

/**
 * Created by song on 17-5-30.
 */
public class AvailablePanel extends JPanel {
    private final JPanel parent;
    
    public AvailablePanel(JPanel parent) {
        this.parent = parent;
    }
    
    public JPanel getParentPanel() {
        return parent;
    }
}
