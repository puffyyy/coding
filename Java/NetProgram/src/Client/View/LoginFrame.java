package Client.View;

import Client.ClientCache;
import Client.ClientReceiveThread;
import Client.ClientSetup;
import Client.ClientUtil;
import Client.View.component.JText;
import Common.entity.Request;
import Common.entity.RequestType;
import Common.entity.User;
import org.jb2011.lnf.beautyeye.BeautyEyeLNFHelper;
import org.jb2011.lnf.beautyeye.ch3_button.BEButtonUI;
import org.jb2011.lnf.beautyeye.ch6_textcoms.BEPasswordFieldUI;
import org.jb2011.lnf.beautyeye.ch6_textcoms.BETextFieldUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.*;
import java.util.Properties;

import static Client.ClientUtil.sendRequestAndReceive;
import static Common.entity.ResponseType.OK;

public class LoginFrame {
    private JFrame MainLoginFrame;
    private final JText username = new JText(10);
    private final JPasswordField password = new JPasswordField(10);
    private JLabel user;
    private JLabel pwd;
    private JButton login;
    private JButton register;
    private JCheckBox autologin;
    private JCheckBox remember;
    
    public void showFrame() {
        ImageIcon image = new ImageIcon(getClass().getResource("/image/bgr.png"));// 背景图片
        JLabel label = new JLabel(image);
        label.setBounds(0, 0, 320, 240);
        ((JPanel) MainLoginFrame.getContentPane()).setOpaque(false);
//        ((JPanel) MainLoginFrame.getContentPane()).setLayout(new FlowLayout());
        MainLoginFrame.getLayeredPane().setLayout(null);
        MainLoginFrame.getLayeredPane().add(label, Integer.valueOf(Integer.MIN_VALUE));
        
        MainLoginFrame.setTitle("Login Chatee");
        Toolkit tk = Toolkit.getDefaultToolkit();
        MainLoginFrame.setLocation((tk.getScreenSize().width - 320) / 2,
                (tk.getScreenSize().height - 240) / 2);
        MainLoginFrame.setSize(320, 240);
        MainLoginFrame.setResizable(false);
        MainLoginFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        MainLoginFrame.setVisible(true);
        preDate();
//        MainLoginFrame.pack();
    }
    
    public void preDate() {
        Properties pro = new Properties();
        try {
            InputStream in = new FileInputStream("./src/client.properties");
            pro.load(in);
            String uid = pro.getProperty("uid");
            if (uid != null && !uid.equals("")) {
                username.setText(uid);
                username.setCaretPosition(username.getText().length());
                autologin.setSelected(true);
            }
            String pwd = pro.getProperty("pwd");
            if (pwd != null && !pwd.equals("")) {
                password.setText(pwd);
                remember.setSelected(true);
                password.requestFocus();
                password.setCaretPosition(password.getPassword().length);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public void writeDate(String key, String val) {
        Properties pps = new Properties();
        try {
            InputStream in = new FileInputStream("./src/client.properties");
            pps.load(in);
            in.close();
            pps.put(key, val);
            OutputStream out = new FileOutputStream("./src/client.properties");
            pps.store(out, "update " + key + ":" + val);
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        
    }
    
    public void checkboxSave() {
        if (autologin.isSelected())
            writeDate("uid", username.getText());
        else
            writeDate("uid", "");
        if (remember.isSelected())
            writeDate("pwd", String.valueOf(password.getPassword()));
        else
            writeDate("pwd", "");
        
    }
    
    public void initLogin() {
        MainLoginFrame = new JFrame();
        user = new JLabel("账号 ");
        pwd = new JLabel("密码 ");
        username.setFont(new Font("雅黑", Font.PLAIN, 16));
        username.setUI(new BETextFieldUI());
        username.requestFocusInWindow();
        password.setFont(new Font("雅黑", Font.PLAIN, 16));
        password.setUI(new BEPasswordFieldUI());
        user.setFont(new Font("PingFang SC", Font.BOLD, 14));
        pwd.setFont(new Font("PingFang SC", Font.BOLD, 14));
        password.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                super.keyPressed(e);
                if (e.getKeyCode() == KeyEvent.VK_ENTER)
                    LoginButtonFunction();
            }
        });
        autologin = new JCheckBox("记住账号");
        remember = new JCheckBox("记住密码");
        autologin.setOpaque(false);
        remember.setOpaque(false);
        login = new JButton("登录");
        register = new JButton("注册");
        login.setOpaque(false);
        register.setOpaque(false);
        username.setUI(new BETextFieldUI());
        password.setUI(new BEPasswordFieldUI());
        login.setUI(new BEButtonUI().setNormalColor(BEButtonUI.NormalColor.green));
        login.setForeground(Color.white);
        register.setUI(new BEButtonUI().setNormalColor(BEButtonUI.NormalColor.lightBlue));
        register.setForeground(Color.white);
        login.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                LoginButtonFunction();
            }
        });
        register.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                new RegisterFrame();
            }
        });
        
        JPanel text = new JPanel();
        text.setOpaque(false);
        JPanel upp = new JPanel();
        upp.setOpaque(false);
        upp.add(user);
        upp.add(username);
        GridBagLayout gridBag = new GridBagLayout();
        text.setLayout(gridBag);
        GridBagConstraints c;
        c = new GridBagConstraints();
        c.insets = new Insets(10, 0, 0, 0);
        c.gridx = 0;
        c.gridy = 0;
        c.fill = GridBagConstraints.NONE;
        gridBag.setConstraints(upp, c);
        text.add(upp);
        
        c = new GridBagConstraints();
        upp = new JPanel();
        upp.setOpaque(false);
        upp.add(pwd);
        upp.add(password);
        c.insets = new Insets(0, 0, -5, 0);
        c.gridx = 0;
        c.gridy = 1;
        c.fill = GridBagConstraints.NONE;
        gridBag.setConstraints(upp, c);
        text.add(upp);
        
        c = new GridBagConstraints();
        upp = new JPanel();
        upp.setOpaque(false);
        upp.add(autologin);
        upp.add(remember);
        c.insets = new Insets(10, 0, 10, 0);
        c.gridx = 0;
        c.gridy = 2;
        c.fill = GridBagConstraints.NONE;
        gridBag.setConstraints(upp, c);
        text.add(upp);
        
        MainLoginFrame.add(text, BorderLayout.NORTH);
        upp = new JPanel();
        upp.setOpaque(false);
        upp.add(login, BorderLayout.WEST);
        upp.add(register, BorderLayout.EAST);
        MainLoginFrame.add(upp);
        showFrame();
    }
    
    public LoginFrame() {
        System.setProperty("sun.java2d.noddraw", "true");//translucencyAppleLike
        BeautyEyeLNFHelper.frameBorderStyle = BeautyEyeLNFHelper.FrameBorderStyle.osLookAndFeelDecorated;//generalNoTranslucencyShadow
        try {
            BeautyEyeLNFHelper.launchBeautyEyeLNF();
            UIManager.put("TextAreaUI", null);
        } catch (Exception e) {
            e.printStackTrace();
        }
        UIManager.put("RootPane.setupButtonVisible", false);//隐藏设置按钮
        
        initLogin();
        System.out.println("Client login frame start");
    }
    
    public void LoginButtonFunction() {
        String uid = String.valueOf(username.getText()).trim();
        String pwd = String.valueOf(password.getPassword()).trim();
        if (null == username.getText() || "".equals(username.getText())) {
            JOptionPane.showMessageDialog(null, "账号不能为空");
            return;
        }
        if ("".equals(pwd)) {
            JOptionPane.showMessageDialog(null, "密码不能为空");
            return;
        }
        if ("0".equals(uid) && "0".equals(pwd)) {
            {
                JOptionPane.showMessageDialog(null, "登录成功，欢迎您：" + username.getText());
                ClientCache.currentUser = new User(0, "0", "root", '1');
                new MainFrame();
            }
        } else {
            //send request to server
            if (!ClientCache.isConnected) ClientSetup.connectToServer();
            Request request = new Request(RequestType.LOGIN);
            request.setAttribute("user", new User(Long.parseLong(uid), pwd));
            Request retRequest = null;
            try {
                retRequest = sendRequestAndReceive(request);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            }
            if (retRequest == null) {
                JOptionPane.showMessageDialog(null, "网络错误，请检查网络连接");
                return;
            }
            if (retRequest.getRequestType() == RequestType.LOGIN && OK == retRequest.getAttribute("state")) {
                ClientUtil.initClientDate(retRequest);
                checkboxSave();
                new MainFrame();
                ClientCache.receiveThread = new ClientReceiveThread();
                ClientCache.receiveThread.start();
                this.MainLoginFrame.dispose();
                
            } else
                JOptionPane.showMessageDialog(null, "用户名密码错误，请重新输入");
        }
        
    }
    
    public static void main(String[] args) {
        new LoginFrame();
    }
}
