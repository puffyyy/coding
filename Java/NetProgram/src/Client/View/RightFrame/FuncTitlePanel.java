package Client.View.RightFrame;

import Client.ClientCache;
import Client.View.LeftFrame.AvailablePanel;
import Client.View.MainFrame;
import Client.View.component.RCBorder;
import Client.View.component.VerticalFlowLayout;
import Client.View.utils.Colors;
import Client.View.utils.GBC;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;

public class FuncTitlePanel extends AvailablePanel {
    private static FuncTitlePanel context;
    private static final String productName = "O_O";
    private JPanel titlePanel;
    private JLabel titleLabel;
    
    private JPanel controlPanel;
    private JLabel closeLabel;
    private JLabel maxLabel;
    private JLabel minLabel;
    private JLabel roomInfoButton;
    
    private ImageIcon maxIcon;
    private ImageIcon restoreIcon;
    private boolean windowMax;
    private Rectangle desktopBounds;
    private Rectangle normalBounds;
    private long lastClickTime;
    private static final Point origin = new Point();
    
    public FuncTitlePanel(JPanel parent) {
        super(parent);
        context = this;
        
        initComponents();
        setListeners();
        initView();
        initBounds();
        
    }
    
    private void initComponents() {
        Cursor handCursor = new Cursor(Cursor.HAND_CURSOR);
        maxIcon = new ImageIcon(getClass().getResource("/image/window_max.png"));
        restoreIcon = new ImageIcon(getClass().getResource("/image/window_restore.png"));
        
        titlePanel = new JPanel();
        titlePanel.setLayout(new GridBagLayout());
        
        roomInfoButton = new JLabel();
        roomInfoButton.setIcon(new ImageIcon(getClass().getResource("/image/options.png")));
        roomInfoButton.setHorizontalAlignment(JLabel.CENTER);
        roomInfoButton.setCursor(handCursor);
        roomInfoButton.setVisible(false);
        
        titleLabel = new JLabel();
        titleLabel.setFont(new Font("微软雅黑 Light", Font.BOLD, 20));
        titleLabel.setForeground(Colors.FONT_BLACK);
        titleLabel.setText(productName);
        titleLabel.setCursor(handCursor);
        
        Dimension controlLabelSize = new Dimension(30, 30);
        
        controlPanel = new JPanel();
        controlPanel.setLayout(new FlowLayout(FlowLayout.RIGHT, 0, 0));
        
        closeLabel = new JLabel();
        closeLabel.setBorder(null);
        closeLabel.setIcon(new ImageIcon(getClass().getResource("/image/close.png")));
        closeLabel.setHorizontalAlignment(JLabel.CENTER);
        closeLabel.setOpaque(true);
        closeLabel.setPreferredSize(controlLabelSize);
        closeLabel.setCursor(handCursor);
        
        maxLabel = new JLabel();
        maxLabel.setBorder(null);
        maxLabel.setIcon(maxIcon);
        maxLabel.setHorizontalAlignment(JLabel.CENTER);
        maxLabel.setOpaque(true);
        maxLabel.setPreferredSize(controlLabelSize);
        maxLabel.setCursor(handCursor);
        
        minLabel = new JLabel();
        minLabel.setBorder(null);
        minLabel.setIcon(new ImageIcon(getClass().getResource("/image/window_min.png")));
        minLabel.setHorizontalAlignment(JLabel.CENTER);
        minLabel.setOpaque(true);
        minLabel.setPreferredSize(controlLabelSize);
        minLabel.setCursor(handCursor);
    }
    
    private void initView() {
        setLayout(new VerticalFlowLayout(VerticalFlowLayout.TOP, 0, 0, true, true));
        setBorder(null);
        this.setBorder(new RCBorder(RCBorder.BOTTOM, Colors.LIGHT_GRAY));
        controlPanel.add(minLabel);
        controlPanel.add(maxLabel);
        controlPanel.add(closeLabel);
        add(controlPanel);
        add(titlePanel);
        titlePanel.add(titleLabel, new GBC(0, 0).setFill(GBC.BOTH).setWeight(300, 1).setInsets(5, 5, 0, 0));
        titlePanel.add(roomInfoButton, new GBC(2, 0).setFill(GBC.BOTH).setWeight(1, 1).setInsets(5, 0, 0, 5));
    }
    
    private void initBounds() {
        Toolkit tk = Toolkit.getDefaultToolkit();
        Dimension screenSize = tk.getScreenSize();
        Insets screenInsets = Toolkit.getDefaultToolkit()
                .getScreenInsets(MainFrame.getContext().getGraphicsConfiguration());
        desktopBounds = new Rectangle(
                screenInsets.left, screenInsets.top,
                screenSize.width - screenInsets.left - screenInsets.right,
                screenSize.height - screenInsets.top - screenInsets.bottom);
        
        normalBounds = new Rectangle(
                (screenSize.width - MainFrame.DEFAULT_WIDTH) / 2,
                (screenSize.height - MainFrame.DEFAULT_HEIGHT) / 2,
                MainFrame.DEFAULT_WIDTH,
                MainFrame.DEFAULT_HEIGHT);
        
    }
    
    public static FuncTitlePanel getContext() {
        return context;
    }
    
    public void updateRoomTitle(String title) {
        this.titleLabel.setText(title);
        
        roomInfoButton.setVisible(true);
        RightPanel parent = (RightPanel) getParent();
        parent.showPanel(RightPanel.MESSAGE);
    }
    
    private void setListeners() {
        MouseListener mouseListener = new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                super.mouseReleased(e);
            }
        };
        
        roomInfoButton.addMouseListener(mouseListener);
        MouseAdapter mouseAdapter = new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (System.currentTimeMillis() - lastClickTime < 500) {
                    maxOrRestoreWindow();
                }
                
                lastClickTime = System.currentTimeMillis();
                super.mouseClicked(e);
            }
            
            public void mousePressed(MouseEvent e) {
                // 当鼠标按下的时候获得窗口当前的位置
                origin.x = e.getX();
                origin.y = e.getY();
            }
        };
        
        MouseMotionListener mouseMotionListener = new MouseMotionAdapter() {
            public void mouseDragged(MouseEvent e) {
                // 当鼠标拖动时获取窗口当前位置
                Point p = MainFrame.getContext().getLocation();
                // 设置窗口的位置
                MainFrame.getContext().setLocation(p.x + e.getX() - origin.x, p.y + e.getY()
                        - origin.y);
            }
        };
        MouseAdapter colorListener = new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getComponent() == closeLabel) {
                    MainFrame.getContext().dispose();
                    try {
                        ClientCache.clientSocket.close();
                    } catch (IOException ioException) {
                        ioException.printStackTrace();
                    }
                    System.exit(0);
                } else if (e.getComponent() == maxLabel) {
                    maxOrRestoreWindow();
                } else if (e.getComponent() == minLabel) {
                    MainFrame.getContext().setExtendedState(JFrame.ICONIFIED);
                }
            }
            
            @Override
            public void mouseEntered(MouseEvent e) {
                ((JLabel) e.getSource()).setBackground(Colors.LIGHT_GRAY);
                super.mouseEntered(e);
            }
            
            @Override
            public void mouseExited(MouseEvent e) {
                ((JLabel) e.getSource()).setBackground(Colors.WINDOW_BACKGROUND_LIGHT);
                super.mouseExited(e);
            }
        };
        
        closeLabel.addMouseListener(colorListener);
        maxLabel.addMouseListener(colorListener);
        minLabel.addMouseListener(colorListener);
        
        controlPanel.addMouseListener(mouseAdapter);
        controlPanel.addMouseMotionListener(mouseMotionListener);
        
        this.addMouseListener(mouseAdapter);
        this.addMouseMotionListener(mouseMotionListener);
        
    }
    
    private void maxOrRestoreWindow() {
        if (windowMax) {
            MainFrame.getContext().setBounds(normalBounds);
            maxLabel.setIcon(maxIcon);
            windowMax = false;
        } else {
            MainFrame.getContext().setBounds(desktopBounds);
            maxLabel.setIcon(restoreIcon);
            windowMax = true;
        }
    }
    
    /**
     * 隐藏群成员面板
     */
    public void hideRoomMembersPanel() {
        //todo memberPanel
//        JPanel roomMemberPanel = ((RightBubble) getParentPanel()).getRoomMembersPanel();
//        if (roomMemberPanel.isVisible()) {
//            roomInfoButton.setIcon(new ImageIcon(getClass().getResource("/image/options.png")));
//            roomMemberPanel.setVisible(false);
//        }
    }
    
    /**
     * 显示群成员面板
     */
    public void showRoomMembersPanel() {
//        JPanel roomMemberPanel = ((RightBubble) getParentPanel()).chatPanel.getRoomMembersPanel();
//        roomInfoButton.setIcon(new ImageIcon(getClass().getResource("/image/options_restore.png")));
//        roomMemberPanel.setVisible(true);
    }
    
}
