package entity;

import java.util.ArrayList;
import java.util.List;
import java.util.TreeMap;
import java.util.stream.Collectors;

public class PersonList {
    private static final PersonList instance = new PersonList();
    private final TreeMap<String, Person> curAllUserMap;
    
    public ArrayList<Person> getCurAllUserMap() {
        return new ArrayList<>(curAllUserMap.values());
    }
    
    public static PersonList getInstance() {
        return instance;
    }
    
    private PersonList() {
        curAllUserMap = new TreeMap<>(Person::personIDCompareTo);
    }
    
    public Person getPersonById(String ID) {
        return curAllUserMap.get(ID);
    }
    
    public Person getPersonByName(String name) {
        return curAllUserMap.values().stream().filter(person -> person.getPersonName().equals(name)).findFirst().orElse(null);
    }
    
    public void addPerson(Person p) {
        curAllUserMap.put(p.getPersonId(), p);
    }
    
    public void delPerson(String ID) {
        curAllUserMap.remove(ID);
    }
    
    public boolean isPersonExistedByName(String name) {
        return curAllUserMap.values().stream().anyMatch(person -> person.getPersonName().equals(name));
    }
    
    public boolean isPersonExistedByID(String ID) {
        return curAllUserMap.containsKey(ID);
    }
    
    public boolean isPersonExistedByMobileNumber(String number) {
        return curAllUserMap.values().stream().anyMatch(person -> person.getPersonMobileNumber().equals(number));
    }
    
    public ArrayList<Waiter> getWaiterList() {
        List<Person> personList = new ArrayList<>(curAllUserMap.values());
        return personList.stream().filter(p -> p.getPersonType() == PersonType.Waiter).map(p -> (Waiter) p).collect(Collectors.toCollection(ArrayList::new));
    }
}
