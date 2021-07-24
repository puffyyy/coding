package Client.View.component;

import Client.View.utils.AvatarUtil;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.ImageUtil;
import Common.entity.User;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class AddGroupCellRender extends DefaultListCellRenderer {
    /**
     * 获取列表单元渲染组件
     *
     * @param list
     * @param value 传入的类，如果是User，进行相应判断
     * @param index
     * @param isSelected 是否被选中
     * @param cellHasFocus
     * @return
     */
    @Override
    public Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
        if (value instanceof User) {
            User user = (User) value;
            try {
                setBorder(null);
                String username = " " + user.getUsername() + "         ";
                String newVal = username.substring(0, Math.max(9, user.getUsername().length()))
                        + " Tel:" + user.getPhoneNum();
                BufferedImage img = ImageUtil.toBufferedImage(AvatarUtil.createOrLoadUserAvatar(user).getScaledInstance(30, 30, Image.SCALE_SMOOTH));
                setIcon(new ImageIcon(img));
                setBackground(Colors.WINDOW_BACKGROUND);
                setForeground(Colors.FONT_BLACK);
                setText(newVal);
                setFont(FontUtil.getDefaultFont(12));
                setHorizontalTextPosition(SwingConstants.RIGHT);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        if (isSelected) {
            setBackground(Colors.ITEM_FOCUS);
        }
        return this;
    }
    
}
