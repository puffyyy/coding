package Client.View.component.BubbleTextPanel;

import Client.View.entity.MessageItem;
import Client.View.utils.AvatarUtil;
import Client.View.utils.FontUtil;

import javax.swing.*;
import java.awt.*;

public class LeftBubble extends JPanel {
    private static final long serialVersionUID = 9029457020704524363L;
    private JLabel userImageLbl;
    private JLabel messageLbl;
    private LeftArrowBubble msgPanel;
    public int calH;
    
    public JLabel getUserImageLbl() {
        return userImageLbl;
    }
    
    public LeftArrowBubble getMsgPanel() {
        return msgPanel;
    }

    /**
     * 接收气泡构造方法，将message对象其中的头像图片、消息文本为要素新建接收气泡LeftBubble(JPanel)
     *
     * @param message 消息对象
     */
    public LeftBubble(MessageItem message) {
        setOpaque(false);
        userImageLbl = new JLabel();
        msgPanel = new LeftArrowBubble();
        msgPanel.setOpaque(false);
        messageLbl = new JLabel();
        messageLbl.setFont(FontUtil.getDefaultFont(15));
        messageLbl.setIconTextGap(12);
        messageLbl.setIcon(new ImageIcon(AvatarUtil.createOrLoadUserAvatar(message.getFrom()).getScaledInstance(25, 25, Image.SCALE_SMOOTH)));
        calH = JLabelSetText(messageLbl, message.getContent_time());
        GroupLayout msgPanelLayout = new GroupLayout(msgPanel);
        msgPanel.setLayout(msgPanelLayout);
        msgPanelLayout.setHorizontalGroup(
                msgPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(msgPanelLayout.createSequentialGroup()
                                .addGap(21, 21, 21)//边框间距
                                .addComponent(messageLbl)
                                .addContainerGap(200, Short.MAX_VALUE))
        );
        msgPanelLayout.setVerticalGroup(
                msgPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(msgPanelLayout.createSequentialGroup()
                                .addComponent(messageLbl)
                                .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
    }

    /**
     * 将消息文本嵌入气泡
     *
     * @param jLabel 接收气泡Panel
     * @param longString 消息文本
     * @return 返回文本面积
     */
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
                        > 280) {
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

