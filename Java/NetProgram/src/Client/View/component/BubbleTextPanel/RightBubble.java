package Client.View.component.BubbleTextPanel;

import Client.View.entity.MessageItem;
import Client.View.utils.AvatarUtil;
import Client.View.utils.FontUtil;
import Client.View.utils.ImageUtil;

import javax.swing.*;
import java.awt.*;

public class RightBubble extends JPanel {
    private static final long serialVersionUID = 9029457020704524363L;
    private JLabel messageLbl, userImageLbl;
    private JPanel msgPanel;
    public int calH;
    
    public JLabel getUserImageLbl() {
        return userImageLbl;
    }
    
    public JPanel getMsgPanel() {
        return msgPanel;
    }
    
    public JLabel getMessageLbl() {
        return messageLbl;
    }
    
    public RightBubble(MessageItem message) {
        setOpaque(false);
        messageLbl = new JLabel();
        msgPanel = new RightArrowBubble();
        msgPanel.setOpaque(false);
        userImageLbl = new JLabel();
        userImageLbl.setHorizontalAlignment(JLabel.RIGHT);
        userImageLbl.setIcon(new ImageIcon(AvatarUtil.createOrLoadUserAvatar(message.getFrom()).getScaledInstance(25, 25, Image.SCALE_SMOOTH)));
        userImageLbl.setHorizontalTextPosition(SwingConstants.LEFT);
        userImageLbl.setFont(FontUtil.getDefaultFont(15));
        userImageLbl.setIconTextGap(12);
        calH = JLabelSetText(userImageLbl, message.getContent_time());
        GroupLayout jPanel1Layout = new GroupLayout(msgPanel);
        msgPanel.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
                jPanel1Layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                                .addContainerGap(171, Short.MAX_VALUE)
                                .addComponent(userImageLbl)
                                .addGap(12, 12, 12))
        );
        jPanel1Layout.setVerticalGroup(
                jPanel1Layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(jPanel1Layout.createSequentialGroup()
                                .addComponent(userImageLbl)
                                .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
    }
    
    int JLabelSetText(JLabel jLabel, String longString) {
        StringBuilder builder = new StringBuilder("<html>");
        char[] chars = longString.toCharArray();
        int lines = 1;
        FontMetrics fontMetrics = jLabel.getFontMetrics(jLabel.getFont());
        int start = 0;
        int len = 0;
        while (start + len < longString.length()) {
            while (true) {
                len++;
                if (start + len > longString.length()) break;
                if (fontMetrics.charsWidth(chars, start, len)
                        > 300) {
                    break;
                }
            }
            lines += 1;
            builder.append(chars, start, len - 1).append("<br/>");
            start = start + len - 1;
            len = 0;
        }
        builder.append(chars, start, longString.length() - start);
        builder.append("</html>");
        jLabel.setText(builder.toString());
        return lines * fontMetrics.getHeight();
    }
}
