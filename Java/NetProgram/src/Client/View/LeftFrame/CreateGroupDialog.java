package Client.View.LeftFrame;

import Client.ClientCache;
import Client.View.MainFrame;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.GBC;
import Client.View.utils.component.RCButton;
import Common.entity.User;
import org.jb2011.lnf.beautyeye.ch19_list.MyDefaultListCellRenderer;

import javax.swing.*;
import javax.swing.border.LineBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CreateGroupDialog extends JDialog {
    private static CreateGroupDialog context;
    private JLabel editor;
    private JPanel editorPanel;
    private JTextField groupNameTextField;
    
    private JList<User> selectUserPanel;
    private JPanel buttonPanel;
    private JButton cancelButton;
    private JButton okButton;
    private List<User> userList = new ArrayList<>();
    
    public static final int DIALOG_WIDTH = 580;
    public static final int DIALOG_HEIGHT = 500;
    
    public CreateGroupDialog(Frame owner, boolean modal) {
        super(owner, modal);
        context = this;
        
        initData();
        initComponents();
        initView();
        setListeners();
    }
    
    private void initData() {
        userList = ClientCache.friendUserList;
    }
    
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
        selectUserPanel.setCellRenderer(new MyDefaultListCellRenderer());
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
        
        // 按钮组
        buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout(FlowLayout.RIGHT, 10, 10));
        
        cancelButton = new RCButton("取消");
        cancelButton.setForeground(Colors.FONT_BLACK);
        
        okButton = new RCButton("创建", Colors.MAIN_COLOR, Colors.MAIN_COLOR_DARKER, Colors.MAIN_COLOR_DARKER);
        okButton.setBackground(Colors.PROGRESS_BAR_START);
    }
    
    private void initView() {
        editorPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
        editorPanel.add(editor);
        editorPanel.add(groupNameTextField);
//        editorPanel.add(privateCheckBox);
        
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
//                    selectUserPanel.getSelectedValuesList();
//                    checkRoomExists(roomName);
                }
                
                super.mouseClicked(e);
            }
        });
        selectUserPanel.addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                if (e.getSource() == selectUserPanel)
                    System.out.println(Arrays.deepToString(new List[]{selectUserPanel.getSelectedValuesList()}));
            }
        });
    }

//    private void checkRoomExists(String name)
//    {
//        if (roomService.findByName(name) != null)
//        {
//            showRoomExistMessage(name);
//            okButton.setEnabled(true);
//        }
//        else
//        {
//            List<SelectUserData> list = selectUserPanel.getSelectedUser();
//            String[] usernames = new String[list.size()];
//
//            for (int i = 0; i < list.size(); i++)
//            {
//                usernames[i] = list.get(i).getName();
//            }
//
//            createChannelOrGroup(name, privateCheckBox.isSelected(), usernames);
//        }
//    }
    
    /**
     * 创建Channel或Group
     *
     * @param name
     * @param privateGroup
     * @param usernames
     */
    private void createChannelOrGroup(String name, boolean privateGroup, String[] usernames) {
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        for (int i = 0; i < usernames.length; i++) {
            sb.append("\"" + usernames[i] + "\"");
            if (i < usernames.length - 1) {
                sb.append(",");
            }
        }
        sb.append("]");
        
        JOptionPane.showMessageDialog(MainFrame.getContext(), "创建群聊", "创建群聊", JOptionPane.INFORMATION_MESSAGE);
    }
    
    public static CreateGroupDialog getContext() {
        return context;
    }
    
    public void showRoomExistMessage(String roomName) {
        JOptionPane.showMessageDialog(null, "群组\"" + roomName + "\"已存在", "群组已存在", JOptionPane.WARNING_MESSAGE);
        groupNameTextField.setText("");
        groupNameTextField.requestFocus();
    }
    
}
