package Client.View.LeftFrame;

import Client.ClientCache;
import Client.ClientUtil;
import Client.View.MainFrame;
import Client.View.component.AddGroupCellRender;
import Client.View.component.RCButton;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.GBC;
import Client.View.utils.ImageUtil;
import Common.entity.Notice;
import Common.entity.Request;
import Common.entity.RequestType;
import Common.entity.User;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;

import static Client.ClientUtil.sendRequest;

public class AddFriendDialog extends JDialog {
    private static AddFriendDialog content;
    private JPanel editorPanel;
    private JTextField searchUserField;
    private JButton searchButton;
    private JScrollPane selectUserPanel;
    private JList<User> jList;
    private JPanel buttonPanel;
    private JButton cancelButton;
    private JButton okButton;
    private JLabel noSuchUserLabel;
    private DefaultListModel<User> model;
    public static final int DIALOG_WIDTH = 580;
    public static final int DIALOG_HEIGHT = 500;
    
    public AddFriendDialog(Frame owner, boolean modal) {
        super(owner, modal);
        content = this;
        
        initComponents();
        initView();
        setListeners();
    }
    
    private void initComponents() {
        int posX = MainFrame.getContext().getX();
        int posY = MainFrame.getContext().getY();
        
        posX = posX + (MainFrame.getContext().currentWindowWidth - DIALOG_WIDTH) / 2;
        posY = posY + (MainFrame.getContext().currentWindowHeight - DIALOG_HEIGHT) / 2;
        setBounds(posX, posY, DIALOG_WIDTH, DIALOG_HEIGHT);
        setUndecorated(true);
        
        getRootPane().setBorder(new LineBorder(Colors.DIALOG_BORDER));
        editorPanel = new JPanel();
        searchUserField = new JTextField();
        searchUserField.setPreferredSize(new Dimension(DIALOG_WIDTH * 2 / 3, 35));
        searchUserField.setFont(FontUtil.getDefaultFont(14));
        searchUserField.setForeground(Colors.FONT_BLACK);
        searchUserField.setMargin(new Insets(0, 15, 0, 0));
        searchButton = new RCButton("搜索", Colors.MAIN_COLOR, Colors.MAIN_COLOR_DARKER, Colors.MAIN_COLOR_DARKER);
        searchButton.setBackground(Colors.PROGRESS_BAR_START);
        jList = new JList<>();
        model = new DefaultListModel<>();
        jList.setModel(model);
        jList.setCellRenderer(new AddGroupCellRender());
        jList.setFixedCellHeight(50);
        selectUserPanel = new JScrollPane(jList);
        selectUserPanel.setPreferredSize(new Dimension(100, 200));
        
        noSuchUserLabel = new JLabel();
        noSuchUserLabel.setVisible(false);
        buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout(FlowLayout.RIGHT, 10, 10));
        cancelButton = new RCButton("取消");
        cancelButton.setForeground(Colors.FONT_BLACK);
        okButton = new RCButton("添加", Colors.MAIN_COLOR, Colors.MAIN_COLOR_DARKER, Colors.MAIN_COLOR_DARKER);
        okButton.setBackground(Colors.PROGRESS_BAR_START);
        
    }
    
    private void initView() {
        editorPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 40, 10));
        editorPanel.add(searchUserField);
        editorPanel.add(searchButton);
        buttonPanel.add(noSuchUserLabel, new GBC(0, 0).setWeight(1, 1));
        buttonPanel.add(cancelButton, new GBC(1, 0).setWeight(1, 1).setInsets(15, 20, 0, 0));
        buttonPanel.add(okButton, new GBC(2, 0).setWeight(1, 1));
        
        add(editorPanel, BorderLayout.NORTH);
        add(selectUserPanel, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);
    }
    
    private void setListeners() {
        cancelButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                setVisible(false);
                dispose();
            }
        });
        searchButton.addMouseListener(new MouseAdapter() {
            String pre = "cannot find";
            
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                String searchString = searchUserField.getText().trim();
                if (searchString.equals(pre)) return;
                pre = searchString;
                if (searchString.equals("")) {
                    return;
                }
                Request request = new Request(RequestType.ADD_FRIEND);
                request.setAttribute("method", "user_list");
                request.setAttribute("search", searchString);
                try {
                    sendRequest(request);
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                    System.out.println("send req failed");
                }
            }
        });
        okButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (okButton.isEnabled() && jList.getSelectedIndex() >= 0) {
                    User selected = jList.getSelectedValue();
                    for (User u : ClientCache.friendUserList) {
                        if (u.getUid() == selected.getUid()) {
                            JOptionPane.showMessageDialog(MainFrame.getContext(), "您与" + u.getUsername() + "已经成为好友", "好友申请", JOptionPane.INFORMATION_MESSAGE);
                            return;
                        }
                    }
                    String reason = (String) JOptionPane.showInputDialog(AddFriendDialog.content,
                            "请输入申请理由",
                            "好友申请",
                            JOptionPane.QUESTION_MESSAGE,
                            null,
                            null,
                            "我是");
                    if (reason == null) return;
                    okButton.setEnabled(false);
                    
                    Request request = new Request(RequestType.ADD_FRIEND);
                    Notice noc = new Notice(ClientCache.currentUser.getUid(), selected.getUid(), new Date(), reason, 0);
                    request.setAttribute("method", "add_friend_from");
                    request.setAttribute("notice", noc);
                    request.setAttribute("from", ClientCache.currentUser);
                    JOptionPane.showMessageDialog(MainFrame.getContext(), "已发送好友请求,等待对方同意", "好友申请", JOptionPane.INFORMATION_MESSAGE);
                    okButton.setEnabled(true);
                    try {
                        ClientUtil.sendRequest(request);
                    } catch (IOException ioException) {
                        ioException.printStackTrace();
                        System.out.println("send req failed");
                    }
                }
                
                super.mouseClicked(e);
            }
        });
    }
    
    public void showErrorMessage() {
        noSuchUserLabel.setText("用户" + searchUserField.getText().trim() + "不存在");
        noSuchUserLabel.setIcon(ImageUtil.getIcon(this, "/image/fail.png", 15, 15));
        noSuchUserLabel.setVisible(true);
    }
    
    public static AddFriendDialog getContent() {
        return content;
    }
    
    public void updateListModel(ArrayList<User> list) {
        noSuchUserLabel.setVisible(false);
        model.clear();
        list.forEach(u -> model.addElement(u));
    }
}
