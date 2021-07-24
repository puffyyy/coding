package Client.View.utils;

import Common.entity.User;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.geom.RoundRectangle2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

/**
 * 处理加载头像相关
 */
public class AvatarUtil {
    private static final Color[] colorArr;
    
    static {
        colorArr = new Color[]{
                new Color(244, 67, 54),
                new Color(233, 30, 99),
                new Color(156, 39, 176),
                new Color(103, 58, 183),
                new Color(63, 81, 181),
                new Color(33, 150, 243),
                new Color(3, 169, 244),
                new Color(0, 188, 212),
                new Color(0, 150, 136),
                new Color(76, 175, 80),
                new Color(139, 195, 74),
                new Color(205, 220, 57),
                new Color(255, 193, 7),
                new Color(255, 152, 0),
                new Color(255, 87, 34),
                new Color(121, 85, 72),
                new Color(158, 158, 158),
                new Color(96, 125, 139)
        };
    }
    
    private static final String AVATAR_USER_CACHE_ROOT;
    private static final String CUSTOM_USER_AVATAR_CACHE_ROOT;
    private static final String CUSTOM_GROUP_AVATAR_CACHE_ROOT;
    private static final int DEFAULT_AVATAR = 0;
    public static final int CUSTOM_AVATAR = 1;
    private static final int GROUP_AVATAR = 2;
    private static final Map<Long, Image> userAvatarCache = new HashMap<>();
    private static final Map<Long, Image> groupAvatarCache = new HashMap<>();
    
    static {
        AVATAR_USER_CACHE_ROOT = "./cache/user_avatar";
        
        File file = new File(AVATAR_USER_CACHE_ROOT);
        if (!file.exists()) {
            file.mkdirs();
            System.out.println("创建头像缓存目录：" + file.getAbsolutePath());
        }
        
        CUSTOM_USER_AVATAR_CACHE_ROOT = AVATAR_USER_CACHE_ROOT + "/custom";
        file = new File(CUSTOM_USER_AVATAR_CACHE_ROOT);
        if (!file.exists()) {
            file.mkdirs();
            System.out.println("创建用户自定义头像缓存目录：" + file.getAbsolutePath());
        }
        
        CUSTOM_GROUP_AVATAR_CACHE_ROOT = "./cache/group_avatar";
        file = new File(CUSTOM_GROUP_AVATAR_CACHE_ROOT);
        if (!file.exists()) {
            file.mkdirs();
            System.out.println("创建群组自定义头像缓存目录：" + file.getAbsolutePath());
        }
    }
    
    public static Image createOrLoadUserAvatar(User user) {
        Image avatar;
        Long uid = user.getUid();
        String username = user.getUsername();
        avatar = userAvatarCache.get(uid);
        if (avatar == null) {
            if (user.getPicture() == null) {
                avatar = getCachedImageAvatar(uid, CUSTOM_AVATAR);
                if (avatar == null) {
                    avatar = createAvatar(username, uid);
                }
                userAvatarCache.put(uid, avatar);
            } else {
                userAvatarCache.put(uid, user.getAvatar());
                return user.getAvatar();
            }
        }
        
        return avatar;
    }
    
    /**
     * 刷新用户头像缓存
     *
     * @param uid
     */
    public static void refreshUserAvatarCache(Long uid) {
        userAvatarCache.put(uid, null);
    }
    
    private static Image createAvatar(String sign, Long uid) {
        String drawString;
        if (sign.length() > 1) {
            drawString = sign.substring(0, 1).toUpperCase() + sign.substring(1, 2).toLowerCase();
        } else {
            drawString = sign;
        }
        
        try {
            int width = 200;
            int height = 200;
            
            // 创建BufferedImage对象
            Font font = FontUtil.getDefaultFont(96, Font.PLAIN);
            BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
            // 获取Graphics2D
            Graphics2D g2d = image.createGraphics();
            
            // 抗锯齿
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            // 画图
            g2d.setBackground(getColor(sign));
            g2d.clearRect(0, 0, width, height);
            
            // 文字
            g2d.setFont(font);
            g2d.setPaint(new Color(255, 255, 255));
            FontMetrics fm = g2d.getFontMetrics(font);
            int strWidth = fm.stringWidth(drawString);
            int strHeight = fm.getHeight();
            int x = (width - strWidth) / 2;
            
            g2d.drawString(drawString, x, strHeight);
            
            BufferedImage roundImage = ImageUtil.setRadius(image, width, height, 35);
            
            g2d.dispose();
            File file = new File(AVATAR_USER_CACHE_ROOT + "/" + uid + ".png");
            ImageIO.write(roundImage, "png", file);
            
            return roundImage;
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        
        return null;
    }
    
    private static Color getColor(String username) {
        int position = username.length() % colorArr.length;
        return colorArr[position];
    }
    
    public static void saveUserAvatar(BufferedImage image, Long uid) {
        saveAvatar(image, uid, CUSTOM_AVATAR);
    }
    
    public static void saveGroupAvatar(BufferedImage image, Long gid) {
        saveAvatar(image, gid, GROUP_AVATAR);
    }
    
    private static void saveAvatar(BufferedImage image, Long id, int type) {
        String path = "";
        if (type == DEFAULT_AVATAR) {
            path = AVATAR_USER_CACHE_ROOT + "/" + id + ".png";
        } else if (type == CUSTOM_AVATAR) {
            path = CUSTOM_USER_AVATAR_CACHE_ROOT + "/" + id + ".png";
        } else if (type == GROUP_AVATAR) {
            path = CUSTOM_GROUP_AVATAR_CACHE_ROOT + "/" + id + ".png";
        } else {
            throw new RuntimeException("类型不存在");
        }
        File avatarPath = new File(path);
        try {
            if (image != null) {
                BufferedImage bufferedImage = ImageUtil.setRadius(image, image.getWidth(), image.getHeight(), 35);
                ImageIO.write(bufferedImage, "png", avatarPath);
                if (type == GROUP_AVATAR)
                    groupAvatarCache.put(id, getCachedImageAvatar(id, type));
                else
                    userAvatarCache.put(id, getCachedImageAvatar(id, type));
            } else {
                throw new RuntimeException("头像保存失败，数据为空");
            }
            
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    private static Image getCachedImageAvatar(Long id, int type) {
        if (type != GROUP_AVATAR)
            if (customAvatarExist(id)) {
                String path = CUSTOM_USER_AVATAR_CACHE_ROOT + "/" + id + ".png";
                return readImage(path);
            } else if (defaultAvatarExist(id)) {
                String path = AVATAR_USER_CACHE_ROOT + "/" + id + ".png";
                return readImage(path);
            } else {
                return null;
            }
        else if (groupAvatarExist(id)) {
            String path = CUSTOM_GROUP_AVATAR_CACHE_ROOT + "/" + id + ".png";
            return readImage(path);
        }
        return null;
    }
    
    private static BufferedImage readImage(String path) {
        try {
            return ImageIO.read(new File(path));
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        return null;
    }
    
    public static boolean customAvatarExist(Long uid) {
        String path = CUSTOM_USER_AVATAR_CACHE_ROOT + "/" + uid + ".png";
        File file = new File(path);
        return file.exists();
    }
    
    public static boolean defaultAvatarExist(Long uid) {
        String path = AVATAR_USER_CACHE_ROOT + "/" + uid + ".png";
        File file = new File(path);
        return file.exists();
    }
    
    public static boolean groupAvatarExist(Long uid) {
        String path = groupAvatarCache + "/" + uid + ".png";
        File file = new File(path);
        return file.exists();
    }
    
    public static void deleteCustomAvatar(Long uid) {
        String path = CUSTOM_USER_AVATAR_CACHE_ROOT + "/" + uid + ".png";
        
        File file = new File(path);
        if (file.exists()) {
            file.delete();
        }
    }
    
    public static void deleteDefaultUserAvatar(Long uid) {
        String path = AVATAR_USER_CACHE_ROOT + "/" + uid + ".png";
        
        File file = new File(path);
        if (file.exists()) {
            file.delete();
        }
    }
    
    public static Image createOrLoadGroupAvatar(Long gid, User[] members, String type) {
        Image avatar;
        avatar = groupAvatarCache.get(gid);
        
        if (avatar == null) {
            avatar = getCachedImageAvatar(gid, 2);
            if (avatar == null) {
                System.out.println("create gid avatar " + gid);
                avatar = createGroupAvatar(gid, members);
            }
            groupAvatarCache.put(gid, avatar);
        }
        
        return avatar;
    }
    
    public static void deleteGroupAvatar(Long gid) {
        String path = CUSTOM_GROUP_AVATAR_CACHE_ROOT + "/" + gid + ".png";
        File file = new File(path);
        if (file.exists()) {
            file.delete();
        }
    }
    
    public static Image createGroupAvatar(Long gid, User[] users) {
        
        try {
            int width = 200;
            int height = 200;
            
            // 选择TYPE_INT_ARGB目的在于可创建透明背景的图，否则圆角外的地方会变成黑色
            BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
            
            // 获取Graphics2D
            Graphics2D g2d = image.createGraphics();
            
            // 绘制一个圆角的灰色背景
            g2d.setComposite(AlphaComposite.Src);
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            g2d.setColor(Colors.GROUP_AVATAR_BACKGROUND);
            g2d.fill(new RoundRectangle2D.Float(0, 0, width, height, 35, 35));
            g2d.setComposite(AlphaComposite.SrcAtop);
            
            Rectangle[] rectangles = getSubAvatarPoints(users);
            int max = Math.min(users.length, 9);
            for (int i = 0; i < max; i++) {
                Image avatar = AvatarUtil.createOrLoadUserAvatar(users[i]);
                g2d.drawImage(avatar, rectangles[i].x, rectangles[i].y, rectangles[i].width, rectangles[i].height, null);
            }
            
            g2d.dispose();
            
            // 缓存到磁盘
            File file = new File(CUSTOM_GROUP_AVATAR_CACHE_ROOT + "/" + gid + ".png");
            ImageIO.write(image, "png", file);
            
            return image;
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        
        return null;
    }
    
    private static Rectangle[] getSubAvatarPoints(User[] users) {
        int gap = 8;
        int parentWidth = 200;
        Rectangle[] rectangles = new Rectangle[users.length];
        int x;
        int y;
        
        if (users.length == 1) {
            int childWidth = parentWidth / 2;
            x = (parentWidth - childWidth) / 2;
            rectangles[0] = new Rectangle(x, x, childWidth, childWidth);
        } else if (users.length == 2) {
            int childWidth = (parentWidth - gap * 3) / 2;
            
            // 第一个
            y = (parentWidth - childWidth) / 2;
            Rectangle r1 = new Rectangle(gap, y, childWidth, childWidth);
            
            // 第二个
            x = gap * 2 + childWidth;
            Rectangle r2 = new Rectangle(x, y, childWidth, childWidth);
            
            rectangles[0] = r1;
            rectangles[1] = r2;
        } else if (users.length == 3) {
            int childWidth = (parentWidth - gap * 3) / 2;
            
            // 第一个
            x = (parentWidth - childWidth) / 2;
            y = gap;
            Rectangle r1 = new Rectangle(x, y, childWidth, childWidth);
            
            // 第二个
            x = gap;
            y = childWidth + gap * 2;
            Rectangle r2 = new Rectangle(x, y, childWidth, childWidth);
            
            // 第三个
            x = childWidth + gap * 2;
            Rectangle r3 = new Rectangle(x, y, childWidth, childWidth);
            
            rectangles[0] = r1;
            rectangles[1] = r2;
            rectangles[2] = r3;
        } else if (users.length == 4) {
            int childWidth = (parentWidth - gap * 3) / 2;
            
            Rectangle r1 = new Rectangle(gap, gap, childWidth, childWidth);
            
            x = childWidth + gap * 2;
            Rectangle r2 = new Rectangle(x, gap, childWidth, childWidth);
            
            x = gap;
            y = childWidth + gap * 2;
            Rectangle r3 = new Rectangle(x, y, childWidth, childWidth);
            
            x = childWidth + gap * 2;
            Rectangle r4 = new Rectangle(x, y, childWidth, childWidth);
            
            rectangles[0] = r1;
            rectangles[1] = r2;
            rectangles[2] = r3;
            rectangles[3] = r4;
        } else if (users.length == 5) {
            int childWidth = (parentWidth - gap * 4) / 3;
            
            x = (parentWidth - childWidth * 2 - gap) / 2;
            Rectangle r1 = new Rectangle(x, x, childWidth, childWidth);
            
            y = x;
            x = x + gap + childWidth;
            Rectangle r2 = new Rectangle(x, y, childWidth, childWidth);
            
            y = r1.y + gap + childWidth;
            Rectangle r3 = new Rectangle(gap, y, childWidth, childWidth);
            
            x = gap * 2 + childWidth;
            Rectangle r4 = new Rectangle(x, y, childWidth, childWidth);
            
            x = gap * 3 + childWidth * 2;
            Rectangle r5 = new Rectangle(x, y, childWidth, childWidth);
            
            rectangles[0] = r1;
            rectangles[1] = r2;
            rectangles[2] = r3;
            rectangles[3] = r4;
            rectangles[4] = r5;
        } else if (users.length == 6) {
            int childWidth = (parentWidth - gap * 4) / 3;
            
            y = (parentWidth - childWidth * 2 - gap) / 2;
            Rectangle r1 = new Rectangle(gap, y, childWidth, childWidth);
            
            x = gap * 2 + childWidth;
            Rectangle r2 = new Rectangle(x, y, childWidth, childWidth);
            
            x = gap * 3 + childWidth * 2;
            Rectangle r3 = new Rectangle(x, y, childWidth, childWidth);
            
            y = r1.y + gap + childWidth;
            Rectangle r4 = new Rectangle(gap, y, childWidth, childWidth);
            
            x = gap * 2 + childWidth;
            Rectangle r5 = new Rectangle(x, y, childWidth, childWidth);
            
            x = gap * 3 + childWidth * 2;
            Rectangle r6 = new Rectangle(x, y, childWidth, childWidth);
            
            rectangles[0] = r1;
            rectangles[1] = r2;
            rectangles[2] = r3;
            rectangles[3] = r4;
            rectangles[4] = r5;
            rectangles[5] = r6;
        } else if (users.length == 7) {
            int childWidth = (parentWidth - gap * 4) / 3;
            
            x = (parentWidth - childWidth) / 2;
            Rectangle r1 = new Rectangle(x, gap, childWidth, childWidth);
            
            y = gap * 2 + childWidth;
            Rectangle r2 = new Rectangle(gap, y, childWidth, childWidth);
            
            x = gap * 2 + childWidth;
            Rectangle r3 = new Rectangle(x, y, childWidth, childWidth);
            
            x = gap * 3 + childWidth * 2;
            Rectangle r4 = new Rectangle(x, y, childWidth, childWidth);
            
            y = r2.y + childWidth + gap;
            Rectangle r5 = new Rectangle(gap, y, childWidth, childWidth);
            
            x = gap * 2 + childWidth;
            Rectangle r6 = new Rectangle(x, y, childWidth, childWidth);
            
            x = gap * 3 + childWidth * 2;
            Rectangle r7 = new Rectangle(x, y, childWidth, childWidth);
            
            rectangles[0] = r1;
            rectangles[1] = r2;
            rectangles[2] = r3;
            rectangles[3] = r4;
            rectangles[4] = r5;
            rectangles[5] = r6;
            rectangles[6] = r7;
        } else if (users.length == 8) {
            int childWidth = (parentWidth - gap * 4) / 3;
            
            x = (parentWidth - childWidth * 2 - gap) / 2;
            Rectangle r1 = new Rectangle(x, gap, childWidth, childWidth);
            
            x = x + gap + childWidth;
            Rectangle r2 = new Rectangle(x, gap, childWidth, childWidth);
            
            y = gap * 2 + childWidth;
            Rectangle r3 = new Rectangle(gap, y, childWidth, childWidth);
            
            x = gap * 2 + childWidth;
            Rectangle r4 = new Rectangle(x, y, childWidth, childWidth);
            
            x = gap * 3 + childWidth * 2;
            Rectangle r5 = new Rectangle(x, y, childWidth, childWidth);
            
            y = r3.y + childWidth + gap;
            Rectangle r6 = new Rectangle(gap, y, childWidth, childWidth);
            
            x = gap * 2 + childWidth;
            Rectangle r7 = new Rectangle(x, y, childWidth, childWidth);
            
            x = gap * 3 + childWidth * 2;
            Rectangle r8 = new Rectangle(x, y, childWidth, childWidth);
            
            rectangles[0] = r1;
            rectangles[1] = r2;
            rectangles[2] = r3;
            rectangles[3] = r4;
            rectangles[4] = r5;
            rectangles[5] = r6;
            rectangles[6] = r7;
            rectangles[7] = r8;
        } else if (users.length >= 9) {
            int childWidth = (parentWidth - gap * 4) / 3;
            
            int index = 0;
            for (int i = 1; i <= 3; i++) {
                y = gap * i + (i - 1) * childWidth;
                
                for (int j = 1; j <= 3; j++) {
                    x = gap * j + (j - 1) * childWidth;
                    Rectangle r = new Rectangle(x, y, childWidth, childWidth);
                    
                    rectangles[index++] = r;
                }
            }
        }
        
        return rectangles;
    }
}
