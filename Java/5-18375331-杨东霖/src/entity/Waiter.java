package entity;

import java.util.LinkedList;

public class Waiter extends Person {
    private final LinkedList<Order> servedOrderList;
    private final LinkedList<Order> unmanagedOrderList;
    public int inChargeCount;
    
    public Waiter(String personId, String userName, char sex, String personMobileNumber) {
        super(personId, userName, sex, personMobileNumber, PersonType.Waiter);
//        servedCustomerList = new ArrayList<>();
        servedOrderList = new LinkedList<>();
        unmanagedOrderList = new LinkedList<>();
        inChargeCount = 0;
    }
    
    public static Waiter addPerson(String personId, String userName, char sex, String personMobileNumber) {
        Waiter p = new Waiter(personId, userName, sex, personMobileNumber);
        PersonList.getInstance().addPerson(p);
        return p;
    }
    
    public LinkedList<Order> getServedOrderList() {
        return servedOrderList;
    }
    
    public LinkedList<Order> getUnmanagedOrderList() {
        return unmanagedOrderList;
    }

    public void addOrder(Order o) {
        servedOrderList.add(o);
        unmanagedOrderList.add(o);
        inChargeCount += 1;
    }
    
    public void serveOrderCntDec() {
        inChargeCount -= 1;
    }
    public int getInChargeCount(){return inChargeCount;}
    
    public void manageOrder() {
        Kitchen.getInstance().addOrder(unmanagedOrderList.pollFirst());
    }
}
