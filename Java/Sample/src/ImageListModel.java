import javax.swing.*;
import java.util.ArrayList;
import java.util.List;

public class ImageListModel extends DefaultListModel<String> {
    private static final long serialVersionUID = 1L;
    private final List<String> imageName = new ArrayList<>();
    public void addElement(String string){
        this.imageName.add(string);
    }
    public int getSize(){
        return imageName.size();
    }
    public String getElementAt(int index){
        return imageName.get(index);
    }
}