package Client.View.LeftFrame;

import Client.ClientCache;
import Client.ClientUtil;
import Client.View.MainFrame;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.IconUtil;
import Client.View.utils.component.RCButton;
import Client.View.utils.component.RCPasswordField;
import Client.View.utils.component.VerticalFlowLayout;
import Common.entity.Request;
import Common.entity.RequestType;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;

public class ChangePasswordPanel extends JPanel {
    private static ChangePasswordPanel context;
    private RCPasswordField textField;
    private RCPasswordField textFieldConfirm;
    private RCButton okButton;
    private JPanel contentPanel;
    private JLabel statusLabel;
    
    public ChangePasswordPanel() {
        context = this;
        
        initComponents();
        initView();
        setListener();
        textField.requestFocus();
    }
    
    private void initComponents() {
        textField = new RCPasswordField();
        textField.setPlaceholder("新密码");
        textField.setPreferredSize(new Dimension(200, 35));
        textField.setFont(FontUtil.getDefaultFont(14));
        textField.setForeground(Colors.FONT_BLACK);
        textField.setMargin(new Insets(0, 15, 0, 0));
        
        textFieldConfirm = new RCPasswordField();
        textFieldConfirm.setPlaceholder("再次输入密码");
        textFieldConfirm.setPreferredSize(new Dimension(200, 35));
        textFieldConfirm.setFont(FontUtil.getDefaultFont(14));
        textFieldConfirm.setForeground(Colors.FONT_BLACK);
        textFieldConfirm.setMargin(new Insets(0, 25, 0, 0));
        
        okButton = new RCButton("确认修改", Colors.MAIN_COLOR, Colors.MAIN_COLOR_DARKER, Colors.MAIN_COLOR_DARKER);
        okButton.setPreferredSize(new Dimension(100, 35));
        okButton.setEnabled(true);
        statusLabel = new JLabel();
        statusLabel.setForeground(Colors.FONT_GRAY_DARKER);
        statusLabel.setVisible(false);
        
        contentPanel = new JPanel();
    }
    
    private void initView() {
        contentPanel.setLayout(new VerticalFlowLayout(VerticalFlowLayout.TOP, 0, 10, true, false));
        contentPanel.add(textField);
        contentPanel.add(textFieldConfirm);
        contentPanel.add(okButton);
        contentPanel.add(statusLabel);
        
        add(contentPanel);
    }
    
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
            okButton.setIcon(IconUtil.getIcon(this, "/image/sending.gif"));
            okButton.setText("修改中...");
            JOptionPane.showMessageDialog(MainFrame.getContext(), "修改密码成功", "修改密码", JOptionPane.INFORMATION_MESSAGE);
            ClientCache.currentUser.setPassword(password);
            // TODO : request send to server
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
    
    public void restoreOKButton() {
        okButton.setText("确认修改");
        okButton.setIcon(null);
        okButton.setEnabled(true);
    }
    
    public void showSuccessMessage() {
        statusLabel.setText("密码修改成功");
        statusLabel.setIcon(IconUtil.getIcon(this, "/image/check.png"));
        statusLabel.setVisible(true);
    }
    
    public void showErrorMessage(String message) {
        statusLabel.setText(message);
        statusLabel.setIcon(new ImageIcon(IconUtil.getIcon(this, "/image/fail.png").getImage().getScaledInstance(15, 15, Image.SCALE_SMOOTH)));
        statusLabel.setVisible(true);
    }
    
    public static ChangePasswordPanel getContext() {
        return context;
    }
}
