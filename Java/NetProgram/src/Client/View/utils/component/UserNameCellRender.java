package Client.View.utils.component;

import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Common.entity.User;

import javax.swing.*;
import java.awt.*;
//todo refactor this cellRender
public class UserNameCellRender extends DefaultListCellRenderer {
    @Override
    public Component getListCellRendererComponent(JList<?> list,Object value, int index, boolean isSelected, boolean cellHasFocus) {
        if (value instanceof User) {
            User user = (User) value;
            try {
                setForeground(Colors.FONT_BLACK);
                setText(user.getUsername()+" \nphone number:"+user.getPhoneNum());
                setFont(FontUtil.getDefaultFont(15));
                setBackground(Colors.ROOM_ITEM_GREY);
                setHorizontalTextPosition(SwingConstants.RIGHT);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        if (isSelected) {
//            System.out.println(index);
            setBackground(Colors.SELECTED_ITEM_GREY);
        }
        return this;
    }
}
