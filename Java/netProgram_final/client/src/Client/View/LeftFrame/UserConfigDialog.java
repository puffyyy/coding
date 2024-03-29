package Client.View.LeftFrame;

import Client.View.MainFrame;
import Client.View.component.MyBorder;
import Client.View.component.MyScrollBarUI;
import Client.View.component.VerticalFlowLayout;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.GBC;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class UserConfigDialog extends JDialog {
    private static UserConfigDialog context;
    private JPanel buttonPanel;
    //private JButton cancelButton;
    private JButton okButton;
    
    private JPanel settingPanel;
    private JPanel settingMenuPanel;
    private JPanel settingAreaPanel;
    private JLabel changeAvatarLabel;
    private JLabel changePasswordLabel;
    private JLabel meLabel;
    
    private ChangeAvatarPanel changeAvatarPanel;
    private ChangePasswordPanel changePasswordPanel;
    private MePanel mePanel;
    
    private JLabel selectedLabel;
    
    public static final String CHANGE_AVATAR = "CHANGE_AVATAR";
    public static final String CHANGE_PASSWORD = "CHANGE_PASSWORD";
    public static final String ME = "ME";
    
    private CardLayout cardLayout = new CardLayout();
    
    public static final int DIALOG_WIDTH = 580;
    public static final int DIALOG_HEIGHT = 500;
    private Cursor handCursor;

    /**
     * 用户布局会话框构造方法
     * @param owner 父框架
     * @param modal 布尔值，代表添加模式
     */
    public UserConfigDialog(Frame owner, boolean modal) {
        super(owner, modal);
        context = this;
        
        initComponents();
        initData();
        
        initView();
        setListeners();
    }

    /**
     * 初始化数据，但未用到
     */
    private void initData() {
    
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
        
        // 按钮组
        buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout(FlowLayout.RIGHT, 10, 10));
        okButton = new MyScrollBarUI.MyButton("关闭", Colors.MAIN_COLOR, Colors.MAIN_COLOR_DARKER, Colors.MAIN_COLOR_DARKER);//rc
        okButton.setPreferredSize(new Dimension(75, 30));
        
        // 设置面板
        settingPanel = new JPanel();
        
        settingMenuPanel = new JPanel();
        settingAreaPanel = new JPanel();
        settingAreaPanel.setBorder(new MyBorder(MyBorder.LEFT, Colors.SCROLL_BAR_TRACK_LIGHT));
        
        handCursor = new Cursor(Cursor.HAND_CURSOR);
        
        // 设置头像按钮
        changeAvatarLabel = new JLabel("更改头像");
        processButtonLabel(changeAvatarLabel);
        
        // 更改密码按钮
        changePasswordLabel = new JLabel("修改密码");
        processButtonLabel(changePasswordLabel);
        
        // "我" 按钮
        meLabel = new JLabel("我");
        processButtonLabel(meLabel);
        
        // 更改头像面板
        changeAvatarPanel = new ChangeAvatarPanel();
        
        // 更改密码面板
        changePasswordPanel = new ChangePasswordPanel();
        
        // "我" 面板
        mePanel = new MePanel();
    }

    /**
     * 初始化视图
     */
    private void initView() {
        //buttonPanel.add(cancelButton, new GBC(0, 0).setWeight(1, 1).setInsets(15, 0, 0, 0));
        buttonPanel.add(okButton, new GBC(1, 0).setWeight(1, 1));
        
        settingPanel.setLayout(new GridBagLayout());
        settingPanel.add(settingMenuPanel, new GBC(0, 0).setWeight(1, 1).setFill(GBC.BOTH).setInsets(10, 0, 0, 0));
        settingPanel.add(settingAreaPanel, new GBC(1, 0).setWeight(6, 1).setFill(GBC.BOTH).setInsets(10, 0, 0, 0));
        
        settingMenuPanel.setLayout(new VerticalFlowLayout(VerticalFlowLayout.TOP, 0, 0, true, false));
        settingMenuPanel.add(meLabel);
        settingMenuPanel.add(changeAvatarLabel);
        settingMenuPanel.add(changePasswordLabel);
        
        settingAreaPanel.setLayout(cardLayout);
        settingAreaPanel.add(mePanel, ME);
        settingAreaPanel.add(changeAvatarPanel, CHANGE_AVATAR);
        settingAreaPanel.add(changePasswordPanel, CHANGE_PASSWORD);
        
        add(settingPanel, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);
        
        selectedLabel(meLabel);
    }

    /**
     * 设置用户布局会话框部分的监听器
     */
    private void setListeners() {
        okButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                setVisible(false);
                
                super.mouseClicked(e);
            }
        });
        
        MouseAdapter itemMouseListener = new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                JLabel source = ((JLabel) e.getSource());
                if (source != selectedLabel) {
                    source.setBackground(Colors.ITEM_SELECTED_LIGHT);
                }
                super.mouseEntered(e);
            }
            
            @Override
            public void mouseExited(MouseEvent e) {
                JLabel source = ((JLabel) e.getSource());
                if (source != selectedLabel) {
                    source.setBackground(Colors.WINDOW_BACKGROUND);
                }
                super.mouseExited(e);
            }
            
            @Override
            public void mouseClicked(MouseEvent e) {
                JLabel source = ((JLabel) e.getSource());
                
                if (source != selectedLabel) {
                    selectedLabel(source);
                    
                    switch (source.getText()) {
                        case "更改头像":
                            cardLayout.show(settingAreaPanel, CHANGE_AVATAR);
                            break;
                        case "修改密码":
                            cardLayout.show(settingAreaPanel, CHANGE_PASSWORD);
                            break;
                        case "我":
                            cardLayout.show(settingAreaPanel, ME);
                            break;
                    }
                }
                
                super.mouseClicked(e);
            }
        };
        
        changeAvatarLabel.addMouseListener(itemMouseListener);
        changePasswordLabel.addMouseListener(itemMouseListener);
        meLabel.addMouseListener(itemMouseListener);
    }

    /**
     * 选定布局中的标签
     * @param label 标签
     */
    private void selectedLabel(JLabel label) {
        selectedLabel = label;
        
        for (Component component : settingMenuPanel.getComponents()) {
            component.setBackground(Colors.WINDOW_BACKGROUND);
        }
        
        label.setBackground(Colors.SCROLL_BAR_TRACK_LIGHT);
    }
    
    public static UserConfigDialog getContext() {
        return context;
    }

    /**
     * 初始化按钮标签
     * @param label 标签（按钮）
     */
    private void processButtonLabel(JLabel label) {
        label.setFont(FontUtil.getDefaultFont(13));
        label.setForeground(Colors.DARKER);
        label.setBorder(new MyBorder(MyBorder.BOTTOM, Colors.SHADOW));
        label.setHorizontalAlignment(SwingConstants.CENTER);
        label.setPreferredSize(new Dimension(50, 30));
        label.setCursor(handCursor);
        label.setOpaque(true);
    }
}
