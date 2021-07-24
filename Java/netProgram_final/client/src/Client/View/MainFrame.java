package Client.View;

import Client.View.LeftFrame.LeftPanel;
import Client.View.RightFrame.RightPanel;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

public class MainFrame extends JFrame {
    public static int DEFAULT_WIDTH = 800;
    public static int DEFAULT_HEIGHT = 650;
    public int currentWindowWidth = DEFAULT_WIDTH;
    public int currentWindowHeight = DEFAULT_HEIGHT;
    
    private LeftPanel leftPanel;
    private RightPanel rightPanel;
    
    private static MainFrame context;

    /**
     * 主框架构造方法，包括内容、子组件和视图的初始化
     */
    public MainFrame() {
        context = this;
        initComponents();
        initView();
    }
    
    public static MainFrame getContext() {
        return context;
    }

    /**
     * 初始化子组件
     */
    private void initComponents() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        leftPanel = new LeftPanel();
        leftPanel.setPreferredSize(new Dimension(260, currentWindowHeight));
        rightPanel = new RightPanel();
        rightPanel.setPreferredSize(new Dimension(540, currentWindowHeight));
    }

    /**
     * 初始化视图
     */
    private void initView() {
        setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        setMinimumSize(new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT));
        setUndecorated(true);
        try {
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
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

    /**
     * 设置主监听器
     */
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

