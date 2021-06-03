package Group;

import Group.GroupItem;
import utils.AvatarUtil;
import utils.Colors;
import utils.TimeUtil;

import javax.swing.*;
import java.awt.*;

public class GroupCellRenderPanel<E> extends GroupItemPanel implements ListCellRenderer<E>{
    
    @Override
    public Component getListCellRendererComponent(JList<? extends E> list, E value, int index, boolean isSelected, boolean cellHasFocus) {
        if (value instanceof GroupItem) {
            GroupItem item = (GroupItem) value;
            
            
            ImageIcon icon = new ImageIcon(AvatarUtil.createOrLoadUserAvatar(item.getRoomId()).getScaledInstance(40, 40, Image.SCALE_SMOOTH));
            avatar.setIcon(icon);
            roomName.setText(item.getTitle());
            brief.setText(item.getLastMessage());
            if (item.getLastMessage() != null && item.getLastMessage().length() > 15)
            {
                brief.setText(item.getLastMessage().substring(0, 15) + "...");
            }
            else
            {
                brief.setText(item.getLastMessage());
            }
            if (item.getTimestamp() > 0)
            {
                time.setText(TimeUtil.diff(item.getTimestamp()));
            }
            if (item.getUnreadCount() > 0)
            {
                unreadCount.setVisible(true);
//                unreadCount.setText(item.getUnreadCount() + "");
            }
            else
            {
                unreadCount.setVisible(false);
            }
    
            if(isSelected)
            {
                setBackground(Colors.SELECTED_ITEM_GREY);
                unreadCount.setVisible(false);
            }
        }
   
        return this;
    }
    
}
