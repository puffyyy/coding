package Client.View.component.BubbleTextPanel;

import Client.ClientCache;
import Client.View.entity.MessageItem;

import javax.swing.*;
import java.util.ArrayList;

public class HistoryArea extends JPanel {
    GroupLayout.ParallelGroup parallelGroup, parallelGroup1;
    JPanel test;
    
    private int height = 0;

    /**
     * 聊天框主Panel新建组件布局，包括子布局中水平、垂直布局
     */
    public HistoryArea() {
        this.setOpaque(false);
        GroupLayout layout = new GroupLayout(this);
        this.setLayout(layout);
        parallelGroup = layout.createParallelGroup(GroupLayout.Alignment.LEADING);
        parallelGroup1 = layout.createParallelGroup(GroupLayout.Alignment.LEADING);
        layout.setHorizontalGroup(parallelGroup);
        layout.setVerticalGroup(parallelGroup1);
    }

    /**
     * 重置聊天框主Panel，并新建组件布局
     */
    public void init(){
        removeAll();
        GroupLayout layout = new GroupLayout(this);
        this.setLayout(layout);
        parallelGroup = layout.createParallelGroup(GroupLayout.Alignment.LEADING);
        parallelGroup1 = layout.createParallelGroup(GroupLayout.Alignment.LEADING);
        layout.setHorizontalGroup(parallelGroup);
        layout.setVerticalGroup(parallelGroup1);
    }

    /**
     * 接收message对象，将其中的头像图片、消息文本设置为接收气泡Panel的相关要素
     *
     * @param message 消息对象
     */
    public void getMessage(MessageItem message) {
        test = new LeftBubble(message);
        LeftBubble testleft = (LeftBubble) test;
        GroupLayout layout = (GroupLayout) this.getLayout();
        
        parallelGroup.addGroup(layout.createSequentialGroup().addContainerGap().addComponent(testleft.getUserImageLbl())
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING).addComponent(testleft.getMsgPanel(), GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap()
        );
        parallelGroup1.addGroup(layout.createSequentialGroup().addContainerGap().addComponent(testleft.getUserImageLbl())
                .addGap(height, height, height)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(testleft.getMsgPanel(), GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addContainerGap(0, Short.MAX_VALUE)
        );
        height += testleft.calH;
    }

    /**
     * 接收message对象，将其中的头像图片、消息文本设置为发送气泡Panel的相关要素
     *
     * @param message 消息对象
     */
    public void sendMessage(MessageItem message) {
        test = new RightBubble(message);
        RightBubble testright = (RightBubble) test;
        GroupLayout layout = (GroupLayout) this.getLayout();
        
        parallelGroup.addGroup(layout.createSequentialGroup().addContainerGap().addComponent(testright.getMessageLbl())
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING).addComponent(testright.getMsgPanel(), GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap()
        );
        parallelGroup1.addGroup(layout.createSequentialGroup().addContainerGap().addComponent(testright.getMessageLbl())
                .addGap(height, height, height)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(testright.getMsgPanel(), GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addContainerGap(22, Short.MAX_VALUE)
        );
        height += testright.calH;
    }

    /**
     * 将接收的message列表依次转化为接收气泡或发送气泡
     *
     * @param arrayList messageItem消息列表
     */
    public void addMessages(ArrayList<MessageItem> arrayList) {
        for (MessageItem m : arrayList) {
            if (m.getFrom().getUid()==(ClientCache.currentUser.getUid()))
                sendMessage(m);
            else
                getMessage(m);
        }
    }

    /**
     * 将接收的message转化为接收气泡或发送气泡
     *
     * @param m 单一messageItem消息对象
     */
    public void addMessage(MessageItem m) {
        if (m.getFrom().getUid()== ClientCache.currentUser.getUid())
            sendMessage(m);
        else
            getMessage(m);
        this.validate();
    }
    
}
