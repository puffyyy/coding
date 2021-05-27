package Client.View.LeftFrame;

import Client.View.MainFrame;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.GBC;
import Client.View.utils.component.RCButton;
import Common.entity.User;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class AddFriendDialog extends JDialog {
    private static AddFriendDialog content;
    private JPanel editorPanel;
    private JTextField searchUserField;
    private JButton searchButton;
    private JPanel selectUserPanel;
    private JList<User> jList;
    private JPanel buttonPanel;
    private JButton cancelButton;
    private JButton okButton;
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
        
        selectUserPanel = new JPanel();
        selectUserPanel.setSize(100, 100);

//        ContractsScrollList JUserList = new ContractsScrollList()
        
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
        
        buttonPanel.add(cancelButton, new GBC(0, 0).setWeight(1, 1).setInsets(15, 0, 0, 0));
        buttonPanel.add(okButton, new GBC(1, 0).setWeight(1, 1));
        
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
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                //TODO : send request to server to find user
            }
        });
        okButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (okButton.isEnabled()) {
                    okButton.setEnabled(false);
                    
                    JOptionPane.showMessageDialog(MainFrame.getContext(), "已发送好友请求", "已发送好友请求", JOptionPane.INFORMATION_MESSAGE);
                    //TODO : send request to server to add friend
                }
                
                super.mouseClicked(e);
            }
        });
    }
    public static AddFriendDialog getContent() {
        return content;
    }

}
