package entity;

import java.util.LinkedList;

public class Kitchen {
    public LinkedList<Order> orderList;
    
    public static Kitchen instance = new Kitchen();
    
    private Kitchen() {
        this.orderList = new LinkedList<>();
    }
    
    public static Kitchen getInstance() {
        return instance;
    }
    
    public void addOrder(Order o) {
        orderList.add(o);
    }
    
    public Order cook() {
        if (orderList.peekFirst() != null) {
            orderList.peekFirst().setCooked(true);
            return orderList.pollFirst();
        }
        return null;
    }
}
