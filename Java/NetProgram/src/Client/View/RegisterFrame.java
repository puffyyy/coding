package Client.View;

import Client.ClientCache;
import Client.ClientSetup;
import Client.ClientUtil;
import Client.View.component.VerticalFlowLayout;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;
import Client.View.utils.GBC;
import Common.entity.Request;
import Common.entity.RequestType;
import Common.entity.User;
import org.jb2011.lnf.beautyeye.ch3_button.BEButtonUI;

import javax.swing.*;
import java.awt.*;
import java.io.IOException;

public class RegisterFrame extends JFrame {
    ImageIcon image;
    
    private boolean checkNickname(String nickname) {
        for (char c : nickname.toCharArray())
            if (!(c >= 32 && c <= 126 && c != ' ')) {
                returnInfo("用户名不合法，不得带有空格等字符！");
                return false;
            }
        if (nickname.trim().equals("")) {
            returnInfo("请输入用户名");
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
        panel.setLayout(new GridBagLayout());
        JPanel leftpanel = new JPanel();
        JPanel rightpanel = new JPanel();
        leftpanel.setLayout(new VerticalFlowLayout(VerticalFlowLayout.TOP, 0, 6, true, false));
//        leftpanel.setSize(70, 400);
        leftpanel.setOpaque(false);
        rightpanel.setLayout(new VerticalFlowLayout(VerticalFlowLayout.TOP, 0, 10, true, false));
        rightpanel.setOpaque(false);
        JPanel user = new JPanel();
        user.setOpaque(false);
        JLabel userLabel = new JLabel("昵   称:");
        userLabel.setFont(FontUtil.getDefaultFont(15));
        userLabel.setForeground(Colors.DARK);
        user.add(userLabel);
        leftpanel.add(user);
        JTextField nameText = new JTextField(12);
        nameText.setFont(FontUtil.getDefaultFont(14));
        rightpanel.add(nameText);
        JPanel phone = new JPanel();
        phone.setOpaque(false);
        JLabel phonenumLabel = new JLabel("手机号:");
        phonenumLabel.setFont(FontUtil.getDefaultFont(15));
        phonenumLabel.setForeground(Colors.DARK);
        phone.add(phonenumLabel);
        leftpanel.add(phone);
        JTextField phonenumText = new JTextField(12);
        phonenumText.setFont(FontUtil.getDefaultFont(14));
        rightpanel.add(phonenumText);
        JPanel pwdPanel = new JPanel();
        pwdPanel.setOpaque(false);
        JLabel pwdLable = new JLabel("密码:");
        pwdLable.setFont(FontUtil.getDefaultFont(14));
        pwdLable.setForeground(Colors.DARK);
        pwdPanel.add(pwdLable);
        leftpanel.add(pwdPanel);
        JTextField pwdText = new JTextField(12);
        pwdText.setFont(FontUtil.getDefaultFont(14));
        rightpanel.add(pwdText);
        JPanel pwdPanel2 = new JPanel();
        pwdPanel2.setOpaque(false);
        JLabel pwdLable2 = new JLabel("验证密码:");
        pwdLable2.setFont(FontUtil.getDefaultFont(14));
        pwdLable2.setForeground(Colors.DARK);
        pwdPanel2.add(pwdLable2);
        leftpanel.add(pwdPanel2);
        JTextField pwdText2 = new JTextField(12);
        pwdText2.setFont(FontUtil.getDefaultFont(14));
        rightpanel.add(pwdText2);
        JButton registerButton = new JButton("注册");
//        registerButton.setPreferredSize(new Dimension(150,30));
        registerButton.setUI(new BEButtonUI());
        registerButton.addActionListener(e -> {
            String nickname = nameText.getText();
            String pwd = pwdText.getText();
            String pwd2 = pwdText2.getText();
            String phonenum = phonenumText.getText();
            if (checkRegister(nickname, pwd, pwd2, phonenum)) {
                User newUser = new User(nickname, pwd, phonenum);
                Request request = new Request(RequestType.REGISTER);
                request.setAttribute("user", newUser);
                if (!ClientCache.isConnected) ClientSetup.connectToServer();
                if (!ClientCache.isConnected) {
                    JOptionPane.showMessageDialog(null, "网络错误，请检查网络连接");
                    return;
                }
                try {
                    Request retReq = ClientUtil.sendRequestAndReceive(request);
                    if (retReq == null) {
                        JOptionPane.showMessageDialog(null, "网络错误，请检查网络连接");
                        return;
                    }
                    User user1 = (User) retReq.getAttribute("user");
                    returnInfo("注册成功! 您的账号为" + user1.getUid() + " 使用账号进行登录");
                    this.dispose();
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                }
                
            }
        });
        JButton cancelButton = new JButton("取消");
        cancelButton.setUI(new BEButtonUI());
        cancelButton.addActionListener(e -> {
            this.dispose();
        });
        JPanel jb = new JPanel();
        jb.setOpaque(false);
        jb.setLayout(new FlowLayout(FlowLayout.RIGHT, 5, 0));
        jb.add(registerButton);
        jb.add(cancelButton);
        panel.add(leftpanel, new GBC(0, 0).setFill(GBC.LINE_START).setWeight(1, 1));//.setInsets(0, 0, 10, 10)
        panel.add(rightpanel, new GBC(1, 0).setFill(GBC.REMAINDER).setWeight(1, 1));//.setInsets(0, 0, 10, 0)
        panel.add(jb, new GBC(1, 1).setFill(GBC.CENTER).setAnchor(GBC.CENTER).setInsets(0, 0, 15, 0));
        
    }
    
    public RegisterFrame() {
        setTitle("注册");
        image = new ImageIcon(getClass().getResource("/image/bgr.png"));// 背景图片
        JLabel label = new JLabel(image);
        label.setBounds(0, 0, 300, 400);
        JPanel panel = (JPanel) this.getContentPane();
        panel.setOpaque(false);
        this.getLayeredPane().setLayout(null);
        registerLable(panel);
        this.getLayeredPane().add(label, Integer.valueOf(Integer.MIN_VALUE));
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        this.setLocation((Toolkit.getDefaultToolkit().getScreenSize().width - 300) / 2,
                (Toolkit.getDefaultToolkit().getScreenSize().height - 400) / 2);
        this.setSize(300, 400);
        this.setVisible(true);
        this.setResizable(false);
    }
    
    public static void main(String[] args) {
        new RegisterFrame();
    }
    
}
