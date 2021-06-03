import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.util.Arrays;
import java.util.List;

public class list_ava {
    public static void main(String[] args) {
        
        JFrame jFrame = new JFrame("列表框与组合框测试");
        String[] item = {"中山大学", "华南理工", "背景大学", "韶关学院"};
        JList list = new JList(item);
        list.setSelectionModel(new DefaultListSelectionModel() {
            @Override
            public void setSelectionInterval(int index0, int index1) {
                if(super.isSelectedIndex(index0)) {
                    super.removeSelectionInterval(index0, index1);
                }
                else {
                    super.addSelectionInterval(index0, index1);
                }
            }
        });
        list.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
        list.addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                if(e.getSource()==list)
                    System.out.println(Arrays.deepToString(new List[]{list.getSelectedValuesList()}));
            }
        });
//        Circle cir = new Circle(2, new Color(1,1,1,1));
//        cir.setVisible(true);
        Container contentPane = jFrame.getContentPane();
        contentPane.setLayout(new GridLayout(1, 2));
        JPanel jp = new JPanel();
        JTextArea ta = new JTextArea(50, 50);
        jp.add(ta);
        contentPane.add(new JScrollPane(list));
        contentPane.add(jp);
        jFrame.setSize(800, 600);
        jFrame.setVisible(true);
    }
    
}
