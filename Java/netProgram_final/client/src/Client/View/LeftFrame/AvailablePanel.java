package Client.View.LeftFrame;

import javax.swing.*;

public class AvailablePanel extends JPanel {
    private final JPanel parent;
    
    public AvailablePanel(JPanel parent) {
        this.parent = parent;
    }
    
    public JPanel getParentPanel() {
        return parent;
    }
}
