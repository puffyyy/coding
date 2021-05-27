package Client.View.utils.component;

import Client.View.utils.Colors;
import Client.View.utils.FontUtil;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import java.awt.*;

public class RCPasswordField extends JPasswordField {
    private String placeholder;
    
    public RCPasswordField() {
        setBackground(Colors.SCROLL_BAR_THUMB);
        setForeground(Colors.FONT_BLACK);
        setCaretColor(Color.WHITE);
        setBorder(null);
        
        getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
            }
            
            @Override
            public void removeUpdate(DocumentEvent e) {
                if (getPassword().length < 1) {
                    repaint();
                }
                
            }
            
            @Override
            public void changedUpdate(DocumentEvent e) {
            
            }
        });
    }
    
    @Override
    protected void paintComponent(Graphics g) {
        
        super.paintComponent(g);
        
        Graphics2D g2 = (Graphics2D) g;
        if (getPassword().length < 1) {
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            g2.setBackground(Color.WHITE);
            g2.setFont(FontUtil.getDefaultFont());
            g2.setColor(Color.WHITE);
            g2.drawString(placeholder, 10, 25);
            g2.dispose();
        }
        
    }
    
    public String getPlaceholder() {
        return placeholder;
    }
    
    public void setPlaceholder(String placeholder) {
        this.placeholder = placeholder;
    }
}
