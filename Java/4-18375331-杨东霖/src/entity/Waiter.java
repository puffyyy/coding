package entity;

import java.util.ArrayList;

public class Waiter extends Person {
    private ArrayList<Customer> servedCustomerList;
    
    public Waiter(String personId, String userName, char sex, String personMobileNumber) {
        super(personId, userName, sex, personMobileNumber, PersonType.Waiter);
        servedCustomerList = new ArrayList<>();
    }
    
    public static Waiter addPerson(String personId, String userName, char sex, String personMobileNumber) {
        Waiter p = new Waiter(personId, userName, sex, personMobileNumber);
        PersonList.getInstance().addPerson(p);
        return p;
    }
}
