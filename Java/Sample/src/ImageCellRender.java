
import utils.AvatarUtil;
import utils.Colors;

import javax.swing.*;
import java.awt.*;
import java.time.ZoneOffset;
import java.time.format.DateTimeFormatter;
import java.util.Date;

public class ImageCellRender<E> extends JPanel implements ListCellRenderer<E> {
    private static final DateTimeFormatter formater = DateTimeFormatter.ofPattern("HH:mm");
    private static final long serialVersionUID = 1L;
    private JPanel JPLeft;
    private JLabel avatar;
    private JLabel jLabelLeftUp;
    private JLabel jLabelLeftDown;
    private JLabel jLabelRight;
    
    public ImageCellRender() {
        super(new FlowLayout(FlowLayout.LEFT, 10, 10));
        JPLeft = new JPanel();
        avatar = new JLabel();
        jLabelLeftUp = new JLabel();
        jLabelLeftDown = new JLabel();
        jLabelRight = new JLabel();
        JPLeft.setLayout(new BorderLayout());
        JPLeft.add(jLabelLeftUp, BorderLayout.NORTH);
        JPLeft.add(jLabelLeftDown, BorderLayout.SOUTH);
        this.add(avatar);
        this.add(JPLeft);
        this.add(jLabelRight);
    }
    
    public Component getListCellRendererComponent(JList<? extends E> list,
                                                  E value, int index, boolean isSelected, boolean cellHasFocus) {
        //this JLabel
        if (value instanceof String) {
            String imageFile = (String) value;
            try {
                setBackground(Colors.ROOM_ITEM_GREY);
                avatar.setIcon(new ImageIcon(AvatarUtil.createOrLoadUserAvatar(imageFile).getScaledInstance(30, 30, Image.SCALE_SMOOTH)));
                JPLeft.setOpaque(false);
                jLabelLeftUp.setText(imageFile);
                jLabelLeftUp.setForeground(Colors.FONT_BLACK);
                
                jLabelLeftDown.setText("recent message");
                jLabelLeftDown.setForeground(Colors.ITEM_FONT_GREY);
                //设置背景色
                jLabelRight.setText(new Date().toInstant().atZone(ZoneOffset.ofHours(8)).toLocalDateTime().format(formater));
                jLabelRight.setForeground(Colors.ITEM_FONT_GREY);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        if (isSelected) {
            System.out.println(index);
            setBackground(Colors.SELECTED_ITEM_GREY);
        }
        
        return this;
    }
}