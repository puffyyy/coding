package Client.View.RightFrame;

import Client.ClientCache;
import Client.ClientUtil;
import Client.View.LeftFrame.AvailablePanel;
import Client.View.LeftFrame.ListPanel;
import Client.View.component.BubbleTextPanel.HistoryArea;
import Client.View.component.MyScrollBarUI;
import Client.View.component.RCBorder;
import Client.View.entity.GroupItem;
import Client.View.entity.MessageItem;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Common.entity.Message;
import Common.entity.Request;
import Common.entity.RequestType;
import org.jb2011.lnf.beautyeye.ch3_button.BEButtonUI;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.plaf.basic.BasicTextAreaUI;
import javax.swing.text.DefaultEditorKit;
import javax.swing.text.JTextComponent;
import javax.swing.text.Keymap;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;

public class ChatPanel extends AvailablePanel {
    
    HistoryArea historyTextArea;
    JTextArea inputArea;
    JScrollPane sendBox;
    JButton send;
    JPanel sendPanel;
    
    JScrollPane messageBox;
    JPanel southPanel;
    
    GroupItem curGroup;
    
    public ChatPanel(JPanel parent) {
        super(parent);
        
        initComponents();
        initView();
        setListeners();
    }
    
    private void initComponents() {
        messageBox = new JScrollPane(historyTextArea);
//        messageBox.setBorder(null);
        messageBox.getVerticalScrollBar().setUI(new MyScrollBarUI());
        messageBox.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        messageBox.setBackground(new Color(245, 245, 245));
    
        newHistory();
        
        inputArea = new JTextArea();
        inputArea.setFont(FontUtil.getDefaultFont(13));
        inputArea.setAutoscrolls(true);
        inputArea.setColumns(50);
        inputArea.setRows(6);
        inputArea.setUI(new BasicTextAreaUI());
        inputArea.setBorder(new EmptyBorder(5, 0, 0, 0));
        inputArea.setLineWrap(true);
        inputArea.setForeground(Colors.FONT_BLACK);
        inputArea.setBorder(new RCBorder(RCBorder.TOP, Colors.DIALOG_BORDER));
        sendPanel = new JPanel();
        sendPanel.setLayout(new FlowLayout(FlowLayout.RIGHT, 20, 0));
        sendPanel.setOpaque(false);
        sendBox = new JScrollPane(inputArea);
        sendBox.setPreferredSize(new Dimension(530, 125));
        sendBox.setBorder(null);
        sendBox.getVerticalScrollBar().setUI(new MyScrollBarUI());
        sendBox.setBackground(Colors.FONT_WHITE);
        sendBox.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        send = new JButton("发送");
        send.setFont(FontUtil.getDefaultFont(14));
        send.setUI(new BEButtonUI());
        send.setToolTipText("按Enter键发送,按Ctrl+Enter键换行");
        sendPanel.add(send);
        southPanel = new JPanel();
    }
    
    private void initView() {
        this.setLayout(new BorderLayout(0, 0));
        setBorder(new EmptyBorder(0, 0, 0, 0));
        setBackground(new Color(245, 245, 245));
        
        southPanel.setLayout(new BorderLayout(0, 0));
        southPanel.setBorder(null);
        southPanel.setBackground(Colors.FONT_WHITE);
        
        southPanel.add(sendBox, BorderLayout.CENTER);
        southPanel.add(sendPanel, BorderLayout.SOUTH);
        
        add(messageBox, BorderLayout.CENTER);
        add(southPanel, BorderLayout.SOUTH);
    }
    
    private void newHistory() {
        historyTextArea = new HistoryArea();
        historyTextArea.setBorder(new EmptyBorder(0, 0, 5, 10));
        historyTextArea.setBackground(new Color(245, 245, 245));
        historyTextArea.setBackground(Colors.SHADOW);
        messageBox.setViewportView(historyTextArea);
    }
    
    private void setListeners() {
        send.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                sendMessage(inputArea.getText());
            }
        });
        Keymap map = JTextComponent.addKeymap("applet keymap", inputArea.getKeymap());
        
        KeyStroke returnKeyStroke = KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, InputEvent.CTRL_MASK);
        Action returnAction = inputArea.getActionMap().get((DefaultEditorKit.insertBreakAction));
        
        map.addActionForKeyStroke(returnKeyStroke, returnAction);
        
        KeyStroke returnKeyStroke2 =
                KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0);
        Action action = new AbstractAction() {
            private static final long serialVersionUID = 5357427076333503068L;
            
            @Override
            public void actionPerformed(ActionEvent e) {
                sendMessage(inputArea.getText());
            }
        };
        map.addActionForKeyStroke(returnKeyStroke2, action);
        inputArea.setKeymap(map);
    }
    
    private void sendMessage(String content) {
        if (inputArea.getText().equals("") || inputArea.getText().equals("\n")) {
            return;
        }
        Date time = new Date();
        Message sendMessageEntity = new Message(ClientCache.currentUser.getUid(), curGroup.getGid(), content, time, 0);
        Request req = new Request(RequestType.SEND_MESSAGE);
        req.setAttribute("message", sendMessageEntity);
        try {
            ClientUtil.sendRequest(req);
        } catch (IOException e) {
            e.printStackTrace();
        }
        historyTextArea.addMessage(new MessageItem(ClientCache.currentUser, content));
        curGroup.messages.add(sendMessageEntity);
        curGroup.updateLastMessage(sendMessageEntity);
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                inputArea.setText("");
            }
        });
        inputArea.requestFocus();
        ListPanel.getContext().refreshRooms();
        JScrollBar vertic = messageBox.getVerticalScrollBar();
        messageBox.validate();
        vertic.setValue(vertic.getMaximum() + 120);
    }
    
    public void setCurGroup(GroupItem g) {
        ((RightPanel) getParentPanel()).getTitlePanel().updateRoomTitle(g.getTitle());
        curGroup = g;
//        historyTextArea.removeAll();
//        historyTextArea.init();
        newHistory();
        ArrayList<MessageItem> messages = new ArrayList<>();
        for (Message mes : g.getMessages()) {
            messages.add(new MessageItem(mes, g));
        }
        historyTextArea.addMessages(messages);
        JScrollBar vertic = messageBox.getVerticalScrollBar();
        messageBox.validate();
        vertic.setValue(vertic.getMaximum());
        
        
    }
    
}
