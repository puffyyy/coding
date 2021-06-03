import java.awt.BorderLayout;
import java.io.File;
import java.io.FileFilter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JScrollPane;

public class JListDemo extends JFrame {
    
    private static final long serialVersionUID = 1L;
    
    public JListDemo() {
        JList<String> list = new JList<>();
        ImageListModel listModel = new ImageListModel();
        
        File[] files = new File("image").listFiles(new FileFilter() {
            public boolean accept(File file) {
                return file.getName().endsWith("png");
            }
        });
        
        ArrayList<String> ltemp = new ArrayList<>();
        for (File file : files) {
            String str = file.getName();
            int index = str.lastIndexOf(".");
            ltemp.add(str.substring(0,index));
            
            System.out.println(str.substring(0,index));
        }
        String[] strList = ltemp.toArray(new String[]{});
        for (String str : strList) {
            listModel.addElement(str);
        }
        list.setModel(listModel);
        list.setCellRenderer(new ImageCellRender());
        
        JScrollPane scrollPane = new JScrollPane(list);
        getContentPane().add(scrollPane, BorderLayout.CENTER);
        getContentPane().add(new JLabel("带图片的Jlist"), BorderLayout.NORTH);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(900, 350, 50, 300);
        
    }
    
    public static void main(String[] args) {
        new JListDemo().setVisible(true);
    }
}