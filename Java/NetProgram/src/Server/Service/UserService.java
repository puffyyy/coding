package Server.Service;

import Common.entity.User;
import Server.DAO.UserDao;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.time.Year;
import java.util.ArrayList;

public class UserService {
    
    public static Long registerNewUser(String username, String password, char sex, String path, String phone_num) {
        Object[] arr = new Object[]{username, password, String.valueOf(sex), path, phone_num};
        return UserDao.insertUser(arr);
    }
    
    public static ArrayList<User> searchUserByKeywords(String key) {
        return addAvatarList(UserDao.selectUserByKeyWords(key));
    }
    
    public static User selectUserById(long id) {
        
        User u = UserDao.selectUserById(id);
        
        return addAvatar(u);
    }
    public static User addAvatar(User u){
        if (u != null) {
            String path = u.getAvatarPath();
            try {
                BufferedImage image = ImageIO.read(new File(path));
                u.setAvatar(image);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return u;
    }
    public static ArrayList<User>addAvatarList(ArrayList<User> list){
        if (list != null) {
            for(User u : list)
            {
                addAvatar(u);
            }
        }
        return list;
    }
}
