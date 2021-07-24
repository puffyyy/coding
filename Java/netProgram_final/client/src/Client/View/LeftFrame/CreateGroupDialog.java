package Client.View.LeftFrame;

import Client.ClientCache;
import Client.ClientUtil;
import Client.View.MainFrame;
import Client.View.component.AddGroupCellRender;
import Client.View.component.MyScrollBarUI;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.GBC;
import Common.entity.Group;
import Common.entity.Request;
import Common.entity.RequestType;
import Common.entity.User;

import javax.swing.*;
import javax.swing.border.LineBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CreateGroupDialog extends JDialog {
    private static CreateGroupDialog context;
    private JLabel editor;
    private JPanel editorPanel;
    private JTextField groupNameTextField;
    private JScrollPane jScrollPane;
    private JList<User> selectUserPanel;
    private JPanel buttonPanel;
    private JButton cancelButton;
    private JButton okButton;
    private List<User> userList = new ArrayList<>();
    
    public static final int DIALOG_WIDTH = 300;
    public static final int DIALOG_HEIGHT = 400;

    /**
     * 创建群组会话构造方法
     * @param owner 拥有者（登录用户）
     * @param modal 布尔值，代表添加模式
     */
    public CreateGroupDialog(Frame owner, boolean modal) {
        super(owner, modal);
        context = this;
        
        initData();
        initComponents();
        initView();
        setListeners();
    }

    /**
     * 初始化群组数据
     */
    private void initData() {
        userList = ClientCache.friendUserList;
    }

    /**
     * 初始化子组件
     */
    private void initComponents() {
        int posX = MainFrame.getContext().getX();
        int posY = MainFrame.getContext().getY();
        posX = posX + (MainFrame.getContext().currentWindowWidth - DIALOG_WIDTH) / 2;
        posY = posY + (MainFrame.getContext().currentWindowHeight - DIALOG_HEIGHT) / 2;
        setBounds(posX, posY, DIALOG_WIDTH, DIALOG_HEIGHT);
        setUndecorated(true);
        
        getRootPane().setBorder(new LineBorder(Colors.DIALOG_BORDER));
        
        editor = new JLabel();
        editorPanel = new JPanel();
        editor.setText("群聊名称");
        editor.setFont(FontUtil.getDefaultFont(14));
        groupNameTextField = new JTextField();
        groupNameTextField.setPreferredSize(new Dimension(DIALOG_WIDTH / 2, 35));
        groupNameTextField.setFont(FontUtil.getDefaultFont(14));
        groupNameTextField.setForeground(Colors.FONT_BLACK);
        groupNameTextField.setMargin(new Insets(0, 15, 0, 0));
        
        selectUserPanel = new JList<>();
        DefaultListModel<User> model = new DefaultListModel<>();
        for (User u : userList) {
            model.addElement(u);
        }
        selectUserPanel.setModel(model);
        selectUserPanel.setFixedCellHeight(40);
        selectUserPanel.setCellRenderer(new AddGroupCellRender());
        selectUserPanel.setSelectionModel(new DefaultListSelectionModel() {
            private static final long serialVersionUID = -4951881422184570829L;
            
            @Override
            public void setSelectionInterval(int index0, int index1) {
                if (super.isSelectedIndex(index0)) {
                    super.removeSelectionInterval(index0, index1);
                } else {
                    super.addSelectionInterval(index0, index1);
                }
            }
        });
        selectUserPanel.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
        jScrollPane = new JScrollPane(selectUserPanel);
        // 按钮组
        buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout(FlowLayout.RIGHT, 10, 10));
        
        cancelButton = new MyScrollBarUI.MyButton("取消");
        cancelButton.setForeground(Colors.FONT_BLACK);
        
        okButton = new MyScrollBarUI.MyButton("创建", Colors.MAIN_COLOR, Colors.MAIN_COLOR_DARKER, Colors.MAIN_COLOR_DARKER);
        okButton.setBackground(Colors.PROGRESS_BAR_START);
    }

    /**
     * 初始化新建群组视图
     */
    private void initView() {
        editorPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
        editorPanel.add(editor);
        editorPanel.add(groupNameTextField);
//        editorPanel.add(privateCheckBox);
        
        buttonPanel.add(cancelButton, new GBC(0, 0).setWeight(1, 1).setInsets(15, 0, 0, 0));
        buttonPanel.add(okButton, new GBC(1, 0).setWeight(1, 1));
        
        add(editorPanel, BorderLayout.NORTH);
        add(jScrollPane, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);
    }

    /**
     * 在创建群组的操作中添加监听器
     */
    private void setListeners() {
        cancelButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                setVisible(false);
                
                super.mouseClicked(e);
            }
        });
        
        okButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (okButton.isEnabled()) {
                    okButton.setEnabled(false);
                    
                    String roomName = groupNameTextField.getText();
                    if (roomName == null || roomName.isEmpty()) {
                        JOptionPane.showMessageDialog(null, "请输入群聊名称", "请输入群聊名称", JOptionPane.WARNING_MESSAGE);
                        groupNameTextField.requestFocus();
                        okButton.setEnabled(true);
                        return;
                    }
                    if (selectUserPanel.getSelectedValuesList().size() < 2) {
                        JOptionPane.showMessageDialog(null, "请至少选择两个好友", "请至少选择两个好友建立群聊", JOptionPane.WARNING_MESSAGE);
                        okButton.setEnabled(true);
                        return;
                    }
                    Group group = new Group(roomName, new ArrayList<>(selectUserPanel.getSelectedValuesList()));
                    group.getUsers().add(ClientCache.currentUser);
                    Request request = new Request(RequestType.JOIN_GROUP);
                    request.setAttribute("group", group);
                    request.setAttribute("from", ClientCache.currentUser);
                    try {
                        ClientUtil.sendRequest(request);
                    } catch (IOException ioException) {
                        ioException.printStackTrace();
                    }
                }
                super.mouseClicked(e);
            }
        });
    }
    
    public static CreateGroupDialog getContext() {
        return context;
    }
    
    
}
