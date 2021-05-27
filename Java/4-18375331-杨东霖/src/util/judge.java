package util;

import entity.Dish;
import entity.PersonType;

public class judge {
    public static boolean isDouble(String str) {
        String regex = "^[+-]?([1-9]\\d*\\.\\d*|0\\.\\d*[1-9]\\d*|0?\\.\\d+|\\d+)$";
        return str.matches(regex);
    }
    
    public static boolean isInteger(String str) {
        return str.matches("^([-+])?\\d+$");
    }
    
    public static boolean isPositiveInteger(String str) {
        return str.matches("^\\+?[1-9][0-9]*$");
    }
    
    /**
     * class person judge
     */
    public static boolean isPersonIdLegal(String pid) {
        return pid.matches("^((Co)|(Wa)|(Bo)|(Cu))\\d{5}$");
    }
    
    public static boolean isPersonIdLegal(String pid, PersonType type) {
        String regex = "^" + type.toString().substring(0, 2) + "\\d{5}$";
        return pid.matches(regex);
    }
    
    public static boolean isPersonNameLegal(String name) {
        String regex = "^[a-zA-Z0-9]+$";
        return name.matches(regex);
    }
    
    public static boolean isPersonPwdLegal(String pwd) {
        String regex = "^((?=.*[a-zA-Z])(?=.*\\d)[\\x21-\\x7e]{8,18})$";
        //"^((?!^[A-Za-z]+$)(?!^[0-9]+$)[\\x21-\\x7e]{8,18})$" 不能处理 "--------"
        
        return pwd.matches(regex);
    }
    
    public static boolean isPersonSexLegal(char sex) {
        return sex == 'F' || sex == 'M';
    }
    
    public static boolean isPersonMobileNumberLegal(String MobileNumber) {
        if (null == MobileNumber) return false;
        String regex = "^1(([3-7]\\d)|(8[0-7]))\\d{4}0((3[1-9])|([4-6]\\d)|7[01])([01])$";
        return MobileNumber.matches(regex);
    }
    
    public static boolean isPersonMobileNumberLegal(String MobileNumber, char sex) {
        if (null == MobileNumber) return false;
        String regex = "^1(([3-7]\\d)|(8[0-7]))\\d{4}0((3[1-9])|([4-6]\\d)|7[01])" + ((sex == 'M') ? "(0)$" : "(1)$");
        return MobileNumber.matches(regex);
    }
    
    //my func
    static public boolean isDishIdLegal(String did) {
        return did.matches("^[HCO]\\d{6}$");
    }
    
    public static boolean isDishAttributeLegal(String name) {
        return name.matches("^[A-Za-z0-9]+$");
    }
    
    public static boolean isDishAttributeLegal(Double price) {
        return price >= 0;
    }
    
    public static boolean isDishAttributeLegal(Integer total) {
        return total >= 0;
    }
    
    static public boolean isDishAttributeLegal(Dish dish) {
        return isDishIdLegal(dish.getDishId()) && isDishAttributeLegal(dish.getDishName()) && isDishAttributeLegal(dish.getDishPrice()) && isDishAttributeLegal(dish.getDishTotalAmount());
    }
}
