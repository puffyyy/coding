package entity;

import java.util.ArrayList;

public class Customer extends Person {
    private boolean isVIP;
    private boolean isDining;
    private double accountBalance;
    private final ArrayList<Dish> orderedDishList;
    private final ArrayList<Dish> unServedDishList;
    
    public Customer(String personId, String userName, char sex, String personMobileNumber) {
        super(personId, userName, sex, personMobileNumber, PersonType.Customer);
        this.isVIP = false;
        this.isDining = false;
        this.accountBalance = 0;
        orderedDishList = new ArrayList<>();
        unServedDishList = new ArrayList<>();
    }
    
    public static Customer addPerson(String personId, String userName, char sex, String personMobileNumber) {
        Customer p = new Customer(personId, userName, sex, personMobileNumber);
        PersonList.getInstance().addPerson(p);
        return p;
    }
    
    public void recharge(double amount) {
        accountBalance += amount;
    }
    
    public double getAccountBalance() {
        return accountBalance;
    }
    
    public boolean isApplyVIPSuccess() {
        isVIP = accountBalance >= 200;
        return isVIP;
    }
}
