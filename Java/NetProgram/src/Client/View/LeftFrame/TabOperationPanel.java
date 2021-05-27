package Client.View.LeftFrame;

import Client.View.utils.Colors;
import Client.View.utils.GBC;
import Client.View.utils.component.RCBorder;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class TabOperationPanel extends ParentAvailablePanel
{
    private JLabel chatLabel;
    private JLabel contactsLabel;
    private ImageIcon chatIconActive;
    private ImageIcon chatIconNormal;
    private ImageIcon contactIconNormal;
    private ImageIcon contactIconActive;

    private LeftPanel parent;

    public TabOperationPanel(JPanel parent)
    {
        super(parent);

        initComponents();
        initView();
    }

    private void initComponents()
    {
        Cursor handCursor = new Cursor(Cursor.HAND_CURSOR);
        RCBorder rcBorder = new RCBorder(RCBorder.RIGHT);
        rcBorder.setHeightScale(0.2F);

        chatIconActive = new ImageIcon(getClass().getResource("/image/chat_active.png"));
        chatIconNormal = new ImageIcon(getClass().getResource("/image/chat_normal.png"));
        chatLabel = new JLabel();
        chatLabel.setIcon(chatIconActive);
        chatLabel.setBorder(rcBorder);
        chatLabel.setHorizontalAlignment(JLabel.CENTER);
        chatLabel.setCursor(handCursor);
        chatLabel.addMouseListener(new TabItemClickListener());

        contactIconNormal = new ImageIcon(getClass().getResource("/image/contacts_normal.png"));
        contactIconActive = new ImageIcon(getClass().getResource("/image/contacts_active.png"));
        contactsLabel = new JLabel();
        contactsLabel.setIcon(contactIconNormal);
        contactsLabel.setBorder(rcBorder);
        contactsLabel.setHorizontalAlignment(JLabel.CENTER);
        contactsLabel.setCursor(handCursor);
        contactsLabel.addMouseListener(new TabItemClickListener());
        parent = (LeftPanel) getParentPanel();
    }

    private void initView()
    {
        setLayout(new GridBagLayout());
        setBackground(Colors.DARK);
        setBorder(new RCBorder(RCBorder.BOTTOM));
        add(chatLabel, new GBC(0, 0).setFill(GBC.HORIZONTAL).setWeight(1,1).setInsets(0,10,0,10));
        add(contactsLabel, new GBC(1, 0).setFill(GBC.HORIZONTAL).setWeight(1,1).setInsets(0,10,0,10));
    }

    @Override
    protected void printBorder(Graphics g)
    {
        super.printBorder(g);
    }

    class TabItemClickListener extends MouseAdapter {

        @Override
        public void mouseClicked(MouseEvent e)
        {
            if (e.getComponent() == chatLabel)
            {
                chatLabel.setIcon(chatIconActive);
                contactsLabel.setIcon(contactIconNormal);
                parent.getListPanel().showPanel(ListPanel.CHAT);

            } else if (e.getComponent() == contactsLabel)
            {
                chatLabel.setIcon(chatIconNormal);
                contactsLabel.setIcon(contactIconActive);
                parent.getListPanel().showPanel(ListPanel.CONTACTS);
            }
        }
    }
}
