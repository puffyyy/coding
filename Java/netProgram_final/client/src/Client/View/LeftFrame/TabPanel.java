package Client.View.LeftFrame;

import Client.View.component.MyBorder;
import Client.View.utils.Colors;
import Client.View.utils.GBC;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class TabPanel extends AvailablePanel {
    private JLabel chatLabel;
    private JLabel contactsLabel;
    private ImageIcon chatIconActive;
    private ImageIcon chatIconNormal;
    private ImageIcon contactIconNormal;
    private ImageIcon contactIconActive;

    private LeftPanel parent;

    /**
     * 表格区域Panel构造方法
     * @param parent 父Panel
     */
    public TabPanel(JPanel parent) {
        super(parent);

        initComponents();
        initView();
    }

    /**
     * 初始化子组件
     */
    private void initComponents() {
        Cursor handCursor = new Cursor(Cursor.HAND_CURSOR);
        MyBorder myBorder = new MyBorder(MyBorder.RIGHT);
        myBorder.setHeightScale(0.2F);

        chatIconActive = new ImageIcon(getClass().getResource("/image/chat_active.png"));
        chatIconNormal = new ImageIcon(getClass().getResource("/image/chat_normal.png"));
        chatLabel = new JLabel();
        chatLabel.setIcon(chatIconActive);
        chatLabel.setBorder(myBorder);
        chatLabel.setHorizontalAlignment(JLabel.CENTER);
        chatLabel.setCursor(handCursor);
        chatLabel.addMouseListener(new TabItemClickListener());

        contactIconNormal = new ImageIcon(getClass().getResource("/image/contacts_normal.png"));
        contactIconActive = new ImageIcon(getClass().getResource("/image/contacts_active.png"));
        contactsLabel = new JLabel();
        contactsLabel.setIcon(contactIconNormal);
        contactsLabel.setBorder(myBorder);
        contactsLabel.setHorizontalAlignment(JLabel.CENTER);
        contactsLabel.setCursor(handCursor);
        contactsLabel.addMouseListener(new TabItemClickListener());
        parent = (LeftPanel) getParentPanel();
    }

    /**
     * 初始化视图
     */
    private void initView() {
        setLayout(new GridBagLayout());
        setBackground(Colors.DARK);
        setBorder(new MyBorder(MyBorder.BOTTOM));
        add(chatLabel, new GBC(0, 0).setFill(GBC.HORIZONTAL).setWeight(1, 1).setInsets(0, 10, 0, 10));
        add(contactsLabel, new GBC(1, 0).setFill(GBC.HORIZONTAL).setWeight(1, 1).setInsets(0, 10, 0, 10));
    }

    /**
     * 重写printBorder方法，但未做功能改变
     * @param g 初始绘图
     */
    @Override
    protected void printBorder(Graphics g) {
        super.printBorder(g);
    }

    class TabItemClickListener extends MouseAdapter {
        /**
         * 鼠标点击后触发Tab中构件选择
         * @param e 鼠标行为
         */
        @Override
        public void mouseClicked(MouseEvent e) {
            if (e.getComponent() == chatLabel) {
                chatLabel.setIcon(chatIconActive);
                contactsLabel.setIcon(contactIconNormal);
                parent.getListPanel().showPanel(ListPanel.CHAT);

            } else if (e.getComponent() == contactsLabel) {
                chatLabel.setIcon(chatIconNormal);
                contactsLabel.setIcon(contactIconActive);
                parent.getListPanel().showPanel(ListPanel.CONTACTS);
            }
        }
    }
}
