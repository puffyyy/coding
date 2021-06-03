package Client.View.LeftFrame;

import Client.ClientCache;
import Client.View.MainFrame;
import Client.View.component.NoticeItemPanel;
import Client.View.component.RCButton;
import Client.View.component.VerticalFlowLayout;
import Client.View.entity.NoticeItem;
import Client.View.utils.Colors;
import Client.View.utils.FontUtil;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

public class NoticeDialog extends JDialog {
    
    private static NoticeDialog content;
    private JLabel title;
    private JButton cancelButton;
    private JPanel buttonPanel;
    private JScrollPane jScrollPane;
    private ArrayList<NoticeItem> nocModel;
    private JPanel viewPort;
    public static final int DIALOG_WIDTH = 580;
    public static final int DIALOG_HEIGHT = 500;
    
    public NoticeDialog(JFrame context, boolean b) {
        super(context, b);
        content = this;
        
        initComponents();
        initView();
        setModel(ClientCache.noticeList);
        setListeners();
    }
    
    private void initComponents() {
        int posX = MainFrame.getContext().getX();
        int posY = MainFrame.getContext().getY();
        
        posX = posX + (MainFrame.getContext().currentWindowWidth - DIALOG_WIDTH) / 2;
        posY = posY + (MainFrame.getContext().currentWindowHeight - DIALOG_HEIGHT) / 2;
        setBounds(posX, posY, DIALOG_WIDTH, DIALOG_HEIGHT);
        setUndecorated(true);
        getRootPane().setBorder(new LineBorder(Colors.DIALOG_BORDER));
        buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout(FlowLayout.RIGHT, 10, 10));
        cancelButton = new RCButton("关闭");
        cancelButton.setForeground(Colors.FONT_BLACK);
        jScrollPane = new JScrollPane();
        viewPort = new JPanel();
        viewPort.setLayout(new VerticalFlowLayout(VerticalFlowLayout.TOP, 5, 0, true, false));
        jScrollPane.setViewportView(viewPort);
        title = new JLabel("  新的朋友");
        title.setFont(FontUtil.getDefaultFont(20));
    }
    
    private void initView() {
        
        buttonPanel.add(cancelButton);
        add(title, BorderLayout.NORTH);
        add(jScrollPane, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);
    }
    
    private void setListeners() {
        cancelButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                setVisible(false);
                dispose();
            }
        });
        
    }
    
    public static NoticeDialog getContent() {
        return content;
    }
    
    public void setModel(ArrayList<NoticeItem> arr) {
        nocModel = arr;
        viewPort.removeAll();
        for (NoticeItem i : nocModel) {
            viewPort.add(new NoticeItemPanel(i));
        }
    }

//    public static void main(String[] args) {
//        JFrame jf = new JFrame();
//        NoticeDialog noticeDialog = new NoticeDialog(jf, true);
//        User u = new User(1L, "username", "pwd", '1', "123412341", "./cache");
//        u.setAvatar(ImageUtil.toBufferedImage(AvatarUtil.createOrLoadUserAvatar(u)));
//        NoticeItem noc = new NoticeItem(u, 2L, new Date(), "i am gbc", 1);
//        noticeDialog.setModel(new ArrayList<NoticeItem>(Collections.singleton(noc)));
//        JButton jb = new JButton("click");
//        jb.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                noticeDialog.setVisible(true);
//            }
//        });
//        jf.add(jb);
//        jf.pack();
//        jf.setVisible(true);
//
//    }
}
