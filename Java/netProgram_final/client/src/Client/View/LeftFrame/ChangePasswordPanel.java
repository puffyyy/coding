package Client.View.LeftFrame;

import Client.ClientCache;
import Client.ClientUtil;
import Client.View.MainFrame;
import Client.View.component.MyScrollBarUI;
import Client.View.component.MyPasswordField;
import Client.View.component.VerticalFlowLayout;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.ImageUtil;
import Common.entity.Request;
import Common.entity.RequestType;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;

public class ChangePasswordPanel extends JPanel {
    private static ChangePasswordPanel context;
    private MyPasswordField textField;
    private MyPasswordField textFieldConfirm;
    private MyScrollBarUI.MyButton okButton;
    private JPanel contentPanel;
    private JLabel statusLabel;

    /**
     * 修改密码Panel构造方法
     */
    public ChangePasswordPanel() {
        context = this;
        
        initComponents();
        initView();
        setListener();
        textField.requestFocus();
    }

    /**
     * 初始化修改密码Panel的组件
     */
    private void initComponents() {
        textField = new MyPasswordField();
        textField.setPlaceholder("新密码");
        textField.setPreferredSize(new Dimension(200, 35));
        textField.setFont(FontUtil.getDefaultFont(14));
        textField.setForeground(Colors.FONT_BLACK);
        textField.setMargin(new Insets(0, 15, 0, 0));
        
        textFieldConfirm = new MyPasswordField();
        textFieldConfirm.setPlaceholder("再次输入密码");
        textFieldConfirm.setPreferredSize(new Dimension(200, 35));
        textFieldConfirm.setFont(FontUtil.getDefaultFont(14));
        textFieldConfirm.setForeground(Colors.FONT_BLACK);
        textFieldConfirm.setMargin(new Insets(0, 25, 0, 0));
        
        okButton = new MyScrollBarUI.MyButton("确认修改", Colors.MAIN_COLOR, Colors.MAIN_COLOR_DARKER, Colors.MAIN_COLOR_DARKER);
        okButton.setPreferredSize(new Dimension(100, 35));
        okButton.setEnabled(true);
        statusLabel = new JLabel();
        statusLabel.setForeground(Colors.FONT_GRAY_DARKER);
        statusLabel.setVisible(false);
        
        contentPanel = new JPanel();
    }

    /**
     * 初始化修改密码Panel的视图
     */
    private void initView() {
        contentPanel.setLayout(new VerticalFlowLayout(VerticalFlowLayout.TOP, 0, 10, true, false));
        contentPanel.add(textField);
        contentPanel.add(textFieldConfirm);
        contentPanel.add(okButton);
        contentPanel.add(statusLabel);
        
        add(contentPanel);
    }

    /**
     * 设置修改密码时的监听器
     */
    private void setListener() {
        
        okButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                doResetPassword();
                super.mouseClicked(e);
            }
        });
        
        KeyListener keyListener = new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                    doResetPassword();
                }
            }
        };
        textField.addKeyListener(keyListener);
        textFieldConfirm.addKeyListener(keyListener);
    }

    /**
     * 重置密码方法
     */
    private void doResetPassword() {
        if (okButton.isEnabled()) {
            String password = new String(textField.getPassword());
            String passwordConfirm = new String(textFieldConfirm.getPassword());
            
            if (password.isEmpty()) {
                showErrorMessage("请输入新密码");
                textField.requestFocus();
                return;
            } else if (passwordConfirm.isEmpty()) {
                showErrorMessage("请再次输入密码");
                textFieldConfirm.requestFocus();
                return;
            }
            
            if (!password.equals(passwordConfirm)) {
                showErrorMessage("两次输入密码不一致");
                textFieldConfirm.requestFocus();
                return;
            }
            
            statusLabel.setVisible(false);
            okButton.setEnabled(false);
            okButton.setIcon(ImageUtil.getIcon(this, "/image/sending.gif", -1, -1));
            okButton.setText("修改中...");
            JOptionPane.showMessageDialog(MainFrame.getContext(), "修改密码成功", "修改密码", JOptionPane.INFORMATION_MESSAGE);
            ClientCache.currentUser.setPassword(password);
            Request request = new Request(RequestType.CHANGE_PASSWORD);
            request.setAttribute("user", ClientCache.currentUser);
            try {
                ClientUtil.sendRequest(request);
                restoreOKButton();
                showSuccessMessage();
            } catch (IOException e) {
                e.printStackTrace();
                showErrorMessage("修改失败");
            }
        }
    }

    /**
     * “确认修改”按钮
     */
    public void restoreOKButton() {
        okButton.setText("确认修改");
        okButton.setIcon(null);
        okButton.setEnabled(true);
    }

    /**
     * 返回成功信息
     */
    public void showSuccessMessage() {
        statusLabel.setText("密码修改成功");
        statusLabel.setIcon(ImageUtil.getIcon(this, "/image/check.png", -1, -1));
        statusLabel.setVisible(true);
    }

    /**
     * 返回错误信息
     * @param message 具体错误信息文本
     */
    public void showErrorMessage(String message) {
        statusLabel.setText(message);
        statusLabel.setIcon(ImageUtil.getIcon(this, "/image/fail.png", 15, 15));
        statusLabel.setVisible(true);
    }
    
    public static ChangePasswordPanel getContext() {
        return context;
    }
}