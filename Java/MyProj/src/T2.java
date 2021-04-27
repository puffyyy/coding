import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class T2 extends JFrame {
    public T2() {
        super("Test anonymous inner class");
        Container container = getContentPane();
        container.setLayout(new FlowLayout(FlowLayout.CENTER));
        JButton b = new JButton("Press me");
        container.add(b);
        b.addActionListener(new J_ActionListener());
        setSize(100, 80);
        setVisible(true);
    }
    
    public static void main(String[] args) {
        T2 application = new T2();
        application.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}

class J_ActionListener implements ActionListener {
    public void actionPerformed(ActionEvent e) {
        System.out.println("The button is pressed");
    }
}