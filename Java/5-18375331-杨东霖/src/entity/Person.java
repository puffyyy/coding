package entity;

import util.judge;

import java.util.Objects;

public class Person {
    private String personId = "";
    private String personPwd = "oms1921SE";
    private String personName;
    private String personMobileNumber;
    private char sex;
    private PersonType personType;
    
    public Person(String userName, char sex, String personMobileNumber) {
        this.personName = userName;
        this.personMobileNumber = personMobileNumber;
        this.sex = sex;
    }
    
    public Person(String personId, String userName, char sex, String personMobileNumber, PersonType type) {
        this.personId = personId;
        this.personName = userName;
        this.personMobileNumber = personMobileNumber;
        this.sex = sex;
        this.personType = type;
    }
    
    public String getPersonName() {
        return personName;
    }
    
    public void setPersonName(String personName) {
        this.personName = personName;
    }
    
    public PersonType getPersonType() {
        return personType;
    }
    
    public String getPersonMobileNumber() {
        return personMobileNumber;
    }
    
    public void setPersonMobileNumber(String personMobileNumber) {
        this.personMobileNumber = personMobileNumber;
    }
    
    public char getSex() {
        return sex;
    }
    
    public void setSex(char sex) {
        this.sex = sex;
    }
    
    public String getPersonId() {
        return personId;
    }
    
    public void setPersonId(String personId) {
        this.personId = personId;
    }
    
    public String getPersonPwd() {
        return personPwd;
    }
    
    public void setPersonPwd(String personPwd) {
        this.personPwd = personPwd;
    }
    
    public boolean checkPersonPwd(String pwd) {
        return this.getPersonPwd().equals(pwd);
    }
    
    public String toString() {
        return String.format("Name:%s\nSex:%c\nPhone:%s", this.personName, this.sex, this.personMobileNumber);
    }
    
    public static Person addPerson(String name, char sex, String userMobileNumber) {
        if (judge.isPersonSexLegal(sex) && judge.isPersonMobileNumberLegal(userMobileNumber) && null != name) {
            Person p = new Person(name, sex, userMobileNumber);
            PersonList.getInstance().addPerson(p);
            return p;
        } else return null;
    }
    
    @Override
    public int hashCode() {
        return personId.hashCode();
    }
    
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Person)) return false;
        Person p = (Person) o;
        return Objects.equals(getPersonId(), p.getPersonId()) &&
                Objects.equals(getPersonName(), p.getPersonName()) &&
                Objects.equals(getPersonMobileNumber(), p.getPersonMobileNumber());
    }
    
    public String toStringPro() {
        return String.format("PID:%s,Name:%s,Sex:%c,Phone:%s,PWD:%s", this.personId, this.personName, this.sex, this.personMobileNumber, this.personPwd);
    }
    
    static public int personIDCompareTo(String id1, String id2) {
        char ch1 = id1.charAt(1);
        char ch2 = id2.charAt(1);
        if (ch1 == ch2) {
            return id1.substring(2).compareTo(id2.substring(2));
        } else if (ch1 == 'u' || (ch1 == 'a' && ch2 == 'o')) return -1;
        else return 1;
    }
    
}
