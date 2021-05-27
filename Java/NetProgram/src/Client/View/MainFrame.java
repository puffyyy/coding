package Client.View;


import Client.View.LeftFrame.LeftPanel;
import Client.View.RightFrame.RightPanel;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

public class MainFrame extends JFrame {
    public static int DEFAULT_WIDTH = 900;
    public static int DEFAULT_HEIGHT = 650;
    
    public int currentWindowWidth = DEFAULT_WIDTH;
    public int currentWindowHeight = DEFAULT_HEIGHT;
    
    private LeftPanel leftPanel;
    private RightPanel rightPanel;
    
    private static MainFrame context;
    
    public MainFrame() {
        context = this;
        initComponents();
        initView();
    }
    
    public static MainFrame getContext() {
        return context;
    }
    
    private void initComponents() {
        setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);

//        UIManager.put("Label.font", FontUtil.getDefaultFont());
//        UIManager.put("Panel.font", FontUtil.getDefaultFont());
//        UIManager.put("TextArea.font", FontUtil.getDefaultFont());
//        UIManager.put("Panel.background", Colors.WINDOW_BACKGROUND);
//        UIManager.put("CheckBox.background", Colors.WINDOW_BACKGROUND);
        
        leftPanel = new LeftPanel();
        leftPanel.setPreferredSize(new Dimension(260, currentWindowHeight));
        rightPanel = new RightPanel();
        
    }
    
    private void initView() {
        setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        setMinimumSize(new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT));
        
        // 隐藏标题栏
        setUndecorated(true);
        
        String windows = "com.sun.java.swing.plaf.windows.WindowsLookAndFeel";
        try {
            UIManager.setLookAndFeel(windows);
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        setListeners();
        
        add(leftPanel, BorderLayout.WEST);
        add(rightPanel, BorderLayout.CENTER);
        
        centerScreen();
        this.setVisible(true);
    }
    
    /**
     * 使窗口在屏幕中央显示
     */
    private void centerScreen() {
        Toolkit tk = Toolkit.getDefaultToolkit();
        this.setLocation((tk.getScreenSize().width - currentWindowWidth) / 2,
                (tk.getScreenSize().height - currentWindowHeight) / 2);
    }
    
    private void setListeners() {
        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                currentWindowWidth = (int) e.getComponent().getBounds().getWidth();
                currentWindowHeight = (int) e.getComponent().getBounds().getHeight();
            }
        });
    }
    
    public static void main(String[] args) {
        new MainFrame();
    }
}

