package entity;

import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;

import static entity.Dish.dishIDCompareTo;

public class Order {
    private final String orderID;
    private final String customerID;
    private String waiterID;
    private final TreeMap<Dish, Integer> dishMapCnt;
    private boolean isConfirmed;
    private boolean isCooked;
    private boolean isCheckOut;
    
    public Order(String orderID, String customerID) {
        this.orderID = orderID;
        this.customerID = customerID;
        dishMapCnt = new TreeMap<>((o1, o2) -> dishIDCompareTo(o1.getDishId(), o2.getDishId()));
        isConfirmed = false;
        isCooked = false;
        isCheckOut = false;
    }
    
    public void addDish(Dish dish, int cnt) {
        dishMapCnt.merge(dish, cnt, Integer::sum);
        dish.setDishTotalAmount(dish.getDishTotalAmount() - cnt);
    }
    
    public String getOrderID() {
        return orderID;
    }
    
    public String getCustomerID() {
        return customerID;
    }
    
    public String getWaiterID() {
        return waiterID;
    }
    
    public void setWaiterID(String waiterID) {
        this.waiterID = waiterID;
    }
    
    public boolean isConfirmed() {
        return isConfirmed;
    }
    
    public void setConfirmed(boolean confirmed) {
        isConfirmed = confirmed;
    }
    
    public Map<Dish, Integer> getDishMapCnt() {
        return dishMapCnt;
    }
    
    public boolean isCooked() {
        return isCooked;
    }
    
    public void setCooked(boolean cooked) {
        isCooked = cooked;
    }
    
    public int getDishSize() {
        return dishMapCnt.size();
    }
    
    @Override
    public String toString() {
        if (dishMapCnt.size() == 0) return "[]";
        Iterator<Map.Entry<Dish, Integer>> iterator = dishMapCnt.entrySet().iterator();
        Map.Entry<Dish, Integer> entry;
        StringBuilder str = new StringBuilder().append('[');
        while (iterator.hasNext()) {
            entry = iterator.next();
            str.append(entry.getValue().toString()).append(' ').append(entry.getKey().getDishName());
            str.append(',');
        }
        str.setCharAt(str.length() - 1, ']');
        return String.valueOf(str);
    }
    public String orderPriceDetail(){
        if (dishMapCnt.size() == 0) return "[]";
        Iterator<Map.Entry<Dish, Integer>> iterator = dishMapCnt.entrySet().iterator();
        Map.Entry<Dish, Integer> entry;
        Dish dish;
        StringBuilder str = new StringBuilder().append('[');
        while (iterator.hasNext()) {
            entry = iterator.next();
            dish = entry.getKey();
            str.append(String.format("%s %.1f", dish.getDishName(),dish.getDishPrice()*entry.getValue()));
            str.append(',');
        }
        str.setCharAt(str.length() - 1, ']');
        return String.valueOf(str);
    }
    public boolean isCheckOut() {
        return isCheckOut;
    }
    
    public void setCheckOut(boolean checkOut) {
        isCheckOut = checkOut;
    }
    public double calOrderPrice(){
        Map<Dish, Integer> dishes = getDishMapCnt();
        Iterator<Map.Entry<Dish, Integer>> iter = dishes.entrySet().iterator();
        Map.Entry<Dish, Integer> entry;
        Dish dish;
        int cnt;
        double sum = 0.0;
        while (iter.hasNext()) {
            entry = iter.next();
            dish = entry.getKey();
            cnt = entry.getValue();
            sum += dish.getDishPrice() * cnt;
        }
        return sum;
    }
}
