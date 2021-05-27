package Client.View.utils.component;

import Client.View.utils.AvatarUtil;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.ImageUtil;
import Common.entity.User;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.image.BufferedImage;

public class ImageTextCellRender extends DefaultListCellRenderer {
    private static final long serialVersionUID = 1L;
    @Override
    public Component getListCellRendererComponent(JList<?> list,
                                                  Object value, int index, boolean isSelected, boolean cellHasFocus) {
        //this extends JLabel
        if (value instanceof User) {
            User user = (User) value;
            try {
                BufferedImage bimg = ImageUtil.toBufferedImage(user.getAvatar().getScaledInstance(40, 40, Image.SCALE_SMOOTH));
                setIcon(new ImageIcon(bimg));
                setBorder(new EmptyBorder(10, 10, 10, 5));
                this.getInsets(new Insets(10, 0, 10, 0));
                AvatarUtil.saveUserAvatar(bimg, user.getUid());
                setBackground(Colors.WINDOW_BACKGROUND);
                setForeground(Colors.FONT_BLACK);
                setText(" "+user.getUsername());
                setFont(FontUtil.getDefaultFont(15));
                setHorizontalTextPosition(SwingConstants.RIGHT);//居中
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        if (isSelected) {
//            System.out.println(index);
            setBackground(Colors.SELECTED_ITEM_GREY);
        }
//        if(cellHasFocus)
//        {
//            setBackground(Colors.FOCUSED_ITEM_GREY);
//        }
            return this;
    }
}