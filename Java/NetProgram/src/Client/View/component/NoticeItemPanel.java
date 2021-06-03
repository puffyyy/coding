package Client.View.component;

import Client.ClientCache;
import Client.ClientUtil;
import Client.View.MainFrame;
import Client.View.entity.NoticeItem;
import Client.View.utils.AvatarUtil;
import Client.View.utils.FontUtil;
import Common.entity.Notice;
import Common.entity.Request;
import Common.entity.RequestType;
import org.jb2011.lnf.beautyeye.ch3_button.BEButtonUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Date;

public class NoticeItemPanel extends JPanel {
    public JLabel avatar = new JLabel();
    public JLabel message = new JLabel();
    public JPanel but = new JPanel();
    public JButton accept = new JButton("接受");
    public JButton deny = new JButton("拒绝");
    public NoticeItem noc;
    
    public NoticeItemPanel() {
        initComponents();
        initView();
        addListener();
    }
    
    public NoticeItemPanel(NoticeItem noc) {
        initComponents();
        initView();
        addListener();
        setNoc(noc);
        avatar.setIcon(new ImageIcon(AvatarUtil.createOrLoadUserAvatar(noc.getFromUser()).getScaledInstance(40, 40, Image.SCALE_SMOOTH)));
        avatar.setText(noc.getFromUser().getUsername());
        message.setText(noc.getContent());
    }
    
    private void addListener() {
        accept.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("accept");
                Request req = new Request(RequestType.ADD_FRIEND);
                req.setAttribute("notice", new Notice(noc.getSendId(), noc.getGetId(), new Date(), noc.getContent(), 1));
                req.setAttribute("from", ClientCache.currentUser);
                req.setAttribute("method", "add_friend_to");
                req.setAttribute("pass", "yes");
                try {
                    ClientUtil.sendRequest(req);
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                }
                accept.setEnabled(false);
                deny.setEnabled(false);
                JOptionPane.showMessageDialog(MainFrame.getContext(), "已同意对方的好友请求", "好友申请", JOptionPane.INFORMATION_MESSAGE);
                ClientCache.noticeList.remove(noc);
            }
        });
        
        deny.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("deny");
                Request req = new Request(RequestType.ADD_FRIEND);
                req.setAttribute("notice", new Notice(noc.getSendId(), noc.getGetId(), new Date(), noc.getContent(), 1));
                req.setAttribute("from", ClientCache.currentUser);
                req.setAttribute("method", "add_friend_to");
                req.setAttribute("pass", "no");
                try {
                    ClientUtil.sendRequest(req);
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                }
                accept.setEnabled(false);
                deny.setEnabled(false);
                JOptionPane.showMessageDialog(MainFrame.getContext(), "已拒绝对方的好友请求", "好友申请", JOptionPane.INFORMATION_MESSAGE);
                ClientCache.noticeList.remove(noc);
            }
        });
    }
    
    private void initView() {
        setLayout(new BorderLayout(0, 3));
        but.setLayout(new FlowLayout(FlowLayout.RIGHT, 10, 0));
        but.add(accept);
        but.add(deny);
        accept.setUI(new BEButtonUI());
        deny.setUI(new BEButtonUI());
        setBorder(new RCBorder(RCBorder.BOTTOM, Color.black));
        add(avatar, BorderLayout.NORTH);
        add(message, BorderLayout.CENTER);
        add(but, BorderLayout.SOUTH);
    }
    
    public void setNoc(NoticeItem noc) {
        this.noc = noc;
    }
    
    private void initComponents() {
        avatar.setOpaque(false);
        avatar.setFont(FontUtil.getDefaultFont(15));
        avatar.setIconTextGap(5);
        message.setFont(FontUtil.getDefaultFont(14));
//        message.setBorder(new LineBorder(Color.black));
        accept.setFont(FontUtil.getDefaultFont(14));
        deny.setFont(FontUtil.getDefaultFont(14));
    }
}
