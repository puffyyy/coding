package entity;

import java.util.ArrayList;

public class OrderList {
    private final Customer currCustomer;
    public ArrayList<Order> orderList;
    
    public OrderList(Customer customer) {
        currCustomer = customer;
        this.orderList = new ArrayList<>();
    }
    
    public int getOrderCount() {
        return orderList.size();
    }
    
    private Order getLastOrder() {
        if (orderList.size() == 0)
            return null;
        return orderList.get(orderList.size() - 1);
    }
    
    public boolean isAllConfirmed() {
        if (getLastOrder() == null)
            return true;
        return getLastOrder().isConfirmed();
    }
    
    public Waiter findWaiter() {
        ArrayList<Waiter> waiters = PersonList.getInstance().getWaiterList();
        waiters.sort((o1, o2) -> {
            if (o1.getInChargeCount() < o2.getInChargeCount())
                return -1;
            else if (o1.getInChargeCount() > o2.getInChargeCount())
                return 1;
            else return o1.getPersonId().compareTo(o2.getPersonId());
        });
        return waiters.get(0);//assume there is at least one waiter
    }
    
    public Order newOrder() {
        String id = currCustomer.getPersonId() + "_" + (getOrderCount() + 1);
        Order o = new Order(id, currCustomer.getPersonId());
        orderList.add(o);
        return o;
        
    }
    
    public void confirmOrder() {
        if (getLastOrder() != null && !getLastOrder().isConfirmed()) {//!isAllConfirmed()
            Waiter w = findWaiter();
            getLastOrder().setConfirmed(true);
            getLastOrder().setWaiterID(w.getPersonId());
            w.addOrder(getLastOrder());
        }
    }
    
    /**
     * always return an order
     * @return if no order exist then return new order
     */
    public Order getCurNewOrder() {
        if (orderList.size() == 0) {
            return newOrder();
        }
        if (isAllConfirmed())
            return newOrder();
        return getLastOrder();
    }
}
