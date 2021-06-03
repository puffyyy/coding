package Client.View.component.BubbleTextPanel;

import Client.ClientCache;
import Client.View.entity.MessageItem;

import javax.swing.*;
import java.util.ArrayList;

public class HistoryArea extends JPanel {
    GroupLayout.ParallelGroup parallelGroup, parallelGroup1;
    JPanel test;
    
    private int height = 0;
    
    public HistoryArea() {
        this.setOpaque(false);
        GroupLayout layout = new GroupLayout(this);
        this.setLayout(layout);
        parallelGroup = layout.createParallelGroup(GroupLayout.Alignment.LEADING);
        parallelGroup1 = layout.createParallelGroup(GroupLayout.Alignment.LEADING);
        layout.setHorizontalGroup(parallelGroup);
        layout.setVerticalGroup(parallelGroup1);
    }
    public void init(){
        removeAll();
        GroupLayout layout = new GroupLayout(this);
        this.setLayout(layout);
        parallelGroup = layout.createParallelGroup(GroupLayout.Alignment.LEADING);
        parallelGroup1 = layout.createParallelGroup(GroupLayout.Alignment.LEADING);
        layout.setHorizontalGroup(parallelGroup);
        layout.setVerticalGroup(parallelGroup1);
    }
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
    
    public void addMessages(ArrayList<MessageItem> arrayList) {
        for (MessageItem m : arrayList) {
            if (m.getFrom().getUid()==(ClientCache.currentUser.getUid()))
                sendMessage(m);
            else
                getMessage(m);
        }
    }
    
    public void addMessage(MessageItem m) {
        if (m.getFrom().getUid()== ClientCache.currentUser.getUid())
            sendMessage(m);
        else
            getMessage(m);
        this.validate();
    }
    
}
