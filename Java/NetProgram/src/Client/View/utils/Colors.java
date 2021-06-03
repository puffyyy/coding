package Client.View.utils;

import Client.ClientCache;

import java.awt.*;

public class Colors {
    public static final Color RED = new Color(250, 81, 81);
    public static final Color FONT_BLACK = new Color(0, 0, 0);
    public static final Color SHADOW = new Color(221, 221, 221);
    public static final Color GROUP_AVATAR_BACKGROUND = new Color(221, 221, 221);
    public static Color DARK = new Color(30, 30, 30);
    public static Color WINDOW_BACKGROUND = new Color(238, 238, 238);
    public static final Color WINDOW_BACKGROUND_LIGHT = new Color(250, 250, 250);
    
    public static Color SCROLL_BAR_TRACK_LIGHT = new Color(214, 214, 214);
    public static Color FONT_WHITE = new Color(255, 255, 255);
    public static Color FONT_GRAY_DARKER = new Color(152, 152, 152);
    public static Color DARKER = new Color(38, 41, 46);
    public static Color ITEM_SELECTED_LIGHT = new Color(228, 228, 228);
    public static Color LIGHT_GRAY = new Color(222, 222, 222);
    public static Color DIALOG_BORDER = new Color(204, 204, 204);
    public static Color PROGRESS_BAR_START = new Color(178, 226, 129);
    public static Color MAIN_COLOR = new Color(54, 172, 72);
    public static Color MAIN_COLOR_DARKER = new Color(51, 154, 69);
    public static final Color SCROLL_BAR_THUMB = new Color(122, 122, 122);
    public static Color SELECTED_ITEM_GREY = new Color(202, 199, 198);
    public static Color ROOM_ITEM_GREY = new Color(230, 229, 229);
    public static Color ITEM_FONT_GREY = new Color(153, 153, 153);
    public static Color ITEM_FOCUS = new Color(194, 215, 194);
    public static Color[] array = {new Color(75, 123, 143), new Color(214, 208, 148),
            new Color(190, 179, 145), new Color(175, 113, 118),
            new Color(203, 194, 213), new Color(222, 218, 223)};
    
    //todo change array beautiful
    public static Color randColor(long id) {
        return array[(int) (ClientCache.currentUser.getUid() + id) % 6];
    }
}
