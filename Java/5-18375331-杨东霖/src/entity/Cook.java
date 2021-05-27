package entity;

import java.util.ArrayList;

public class Cook extends Person {
    private final ArrayList<Dish> finishedDishList;
    
    public Cook(String personId, String userName, char sex, String personMobileNumber) {
        super(personId, userName, sex, personMobileNumber, PersonType.Cook);
        finishedDishList = new ArrayList<>();
    }
    
    public static Cook addPerson(String personId, String userName, char sex, String personMobileNumber) {
        Cook p = new Cook(personId, userName, sex, personMobileNumber);
        PersonList.getInstance().addPerson(p);
        return p;
    }
}
