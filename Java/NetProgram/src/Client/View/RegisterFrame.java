package Client.View;

import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.component.VerticalFlowLayout;
import Common.entity.User;

import javax.swing.*;
import java.awt.*;

public class RegisterFrame extends JFrame {
    JPanel panel;
    ImageIcon image;
    
    private boolean checkNickname(String nickname) {
        for (char c : nickname.toCharArray())
            if (!(c >= 32 && c <= 126 && c != ' ')) {
                System.out.println("用户名不合法，不得带有空格等字符！");
                return false;
            }
        return true;
    }
    
    private boolean checkPWD(String pwd, String pwd2) {
        if (!pwd.equals(pwd2)) {
            returnInfo("两次输入的密码不一致！");
            return false;
        }
        if (pwd.length() < 1 || pwd.length() > 16) {
            returnInfo("密码长度必须在1~16位之间");
            return false;
        }
        for (char c : pwd.toCharArray()) {
            if (!(c >= 32 && c <= 126 && c != ' ')) {
                returnInfo("密码不合法，不得带有空格等字符！");
                return false;
            }
        }
        return true;
    }
    
    private boolean checkPhonenum(String phonenum) {
        long pnum;
        try {
            pnum = Long.parseLong(phonenum);
        } catch (Exception e) {
            returnInfo("电话号码仅可为11位数字");
            return false;
        }
        if (phonenum.length() != 11) {
            returnInfo("电话号码不存在！");
            return false;
        }
        //其他电话号码匹配原则
        //查找库内有无重复
        return true;
    }
    
    private boolean checkRegister(String nickname, String pwd, String pwd2, String phoneNum) {
        return checkNickname(nickname) && checkPWD(pwd, pwd2) && checkPhonenum(phoneNum);
    }
    
    private void returnInfo(String info) {
        JOptionPane.showMessageDialog(null, info);
    }
    
    private void registerLable(JPanel panel) {
        //todo Split into left and right add component
//        panel.setLayout(new VerticalFlowLayout());
        panel.setLayout(new VerticalFlowLayout(VerticalFlowLayout.TOP, 0, 8, false, false));
        JPanel user = new JPanel();
        user.setOpaque(false);
        JLabel userLabel = new JLabel("昵   称:");
        userLabel.setFont(FontUtil.getDefaultFont(15));
        userLabel.setForeground(Colors.DARK);
        user.add(userLabel);
        
        JTextField nameText = new JTextField(12);
        nameText.setFont(FontUtil.getDefaultFont(14));
        user.add(nameText);
        panel.add(user);
        JPanel phone = new JPanel();
        phone.setOpaque(false);
        JLabel phonenumLabel = new JLabel("手机号:");
        phonenumLabel.setFont(FontUtil.getDefaultFont(15));
        phonenumLabel.setForeground(Colors.DARK);
        phone.add(phonenumLabel);
        
        JTextField phonenumText = new JTextField(12);
        phonenumText.setFont(FontUtil.getDefaultFont(14));
        phone.add(phonenumText);
        panel.add(phone);
        ButtonGroup buttonGroup = new ButtonGroup();
        JRadioButton rb1 = new JRadioButton("男", true);    //创建JRadioButton对象
        rb1.setOpaque(false);
        JRadioButton rb2 = new JRadioButton("女", false);    //创建JRadioButton对象
        rb2.setOpaque(false);
        buttonGroup.add(rb1);
        buttonGroup.add(rb2);
        JPanel buttonLabel = new JPanel(new FlowLayout(FlowLayout.LEFT, 0, 5));
        JLabel jLabel = new JLabel("性别:");
        jLabel.setFont(FontUtil.getDefaultFont(15));
        jLabel.setForeground(Colors.DARK);
        buttonLabel.setOpaque(false);
        buttonLabel.add(jLabel);
        buttonLabel.add(rb1);
        buttonLabel.add(rb2);
        buttonLabel.setForeground(Colors.DARK);
        panel.add(buttonLabel,LEFT_ALIGNMENT);
        
        JPanel pwdPanel = new JPanel();
        pwdPanel.setOpaque(false);
        JLabel pwdLable = new JLabel("密码:");
        pwdLable.setFont(FontUtil.getDefaultFont(14));
        pwdLable.setForeground(Colors.DARK);
        pwdPanel.add(pwdLable);
        JTextField pwdText = new JTextField(12);
        pwdText.setFont(FontUtil.getDefaultFont(14));
        pwdPanel.add(pwdText);
        panel.add(pwdPanel);
        JPanel pwdPanel2 = new JPanel();
        pwdPanel2.setOpaque(false);
        JLabel pwdLable2 = new JLabel("验证密码:");
        pwdLable2.setFont(FontUtil.getDefaultFont(14));
        pwdLable2.setForeground(Colors.DARK);
        pwdPanel2.add(pwdLable2);
        JTextField pwdText2 = new JTextField(12);
        pwdText2.setFont(FontUtil.getDefaultFont(14));
        pwdPanel2.add(pwdText2);
        panel.add(pwdPanel2);
        JButton registerButton = new JButton("注册");
        registerButton.setPreferredSize(new Dimension(150,30));
        registerButton.addActionListener(e -> {
            String nickname = nameText.getText();
            String pwd = pwdText.getText();
            String pwd2 = pwdText2.getText();
            String phonenum = phonenumText.getText();
            if (checkRegister(nickname, pwd, pwd2, phonenum)) {
                User newUser = new User(nickname, pwd, '1');
                //todo get sex
                // send register request to server
                returnInfo("注册成功!");
            }
        });
        panel.add(registerButton,CENTER_ALIGNMENT);
    }
    
    public RegisterFrame() {
        image = new ImageIcon(getClass().getResource("/image/bgr.png"));// 背景图片
        JLabel label = new JLabel(image);
        label.setBounds(0, 0, 300, 400);
        panel = (JPanel) this.getContentPane();
        panel.setOpaque(false);
        panel.setLayout(new FlowLayout());
        this.getLayeredPane().setLayout(null);
        
        
        registerLable(panel);
        this.getLayeredPane().add(label, Integer.valueOf(Integer.MIN_VALUE));
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        this.setBounds(150, 80, 300, 400);
        this.setVisible(true);
        this.setResizable(false);
    }
    
    
}
