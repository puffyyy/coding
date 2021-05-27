package Client.View.utils.component;

import Client.ClientCache;
import Client.View.entity.GroupItem;
import Client.View.utils.AvatarUtil;
import Client.View.utils.Colors;
import Client.View.utils.TimeUtil;
import Common.entity.User;

import javax.swing.*;
import java.awt.*;

public class GroupCellRender<E> extends GroupItemPanel implements ListCellRenderer<E> {
    
    @Override
    public Component getListCellRendererComponent(JList<? extends E> list, E value, int index, boolean isSelected, boolean cellHasFocus) {
        if (value instanceof GroupItem) {
            setBackground(Colors.ROOM_ITEM_GREY);
            GroupItem item = (GroupItem) value;
            ImageIcon icon;
            if (item.getGroupMember().size() == 2) {
                User u = item.getGroupMember().get(0);
                if (u.getUid() == ClientCache.currentUser.getUid())
                    u = item.getGroupMember().get(1);
                icon = new ImageIcon(AvatarUtil.createOrLoadUserAvatar(u)
                        .getScaledInstance(50, 50, Image.SCALE_SMOOTH));
            } else {
                icon = new ImageIcon(AvatarUtil.createOrLoadGroupAvatar(item.getRoomId(), item.getGroupMember().toArray(new User[]{}), "d")
                        .getScaledInstance(50, 50, Image.SCALE_SMOOTH));
            }
            avatar.setIcon(icon);
            roomName.setText(item.getTitle());
            brief.setText(item.getLastText());
            if (item.getLastText() != null && item.getLastText().length() > 15)
                brief.setText(item.getLastText().substring(0, 15) + "...");
            else
                brief.setText(item.getLastText());
            
            if (item.getTimestamp() > 0) {
                time.setText(TimeUtil.diff(item.getTimestamp()));
            }
            unreadCount.setVisible(item.getUnreadCount() > 0);//unreadCount.setText(item.getUnreadCount() + "");
            if (isSelected) {
                setBackground(Colors.SELECTED_ITEM_GREY);
                unreadCount.setVisible(false);
            }
        }
        return this;
    }
    
}
