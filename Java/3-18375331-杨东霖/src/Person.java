public class Person {
    private String personId = "";
    private String personPwd = "oms1921";
    private String userName = "";
    private String personMobileNumber = "";
    private char sex;
    
    public Person() {
    }
    
    public Person(String userName, char sex, String personMobileNumber) {
        this.userName = userName;
        this.personMobileNumber = personMobileNumber;
        this.sex = sex;
    }
    
    public Person(String personId, String userName, char sex, String personMobileNumber) {
        this.personId = personId;
        this.userName = userName;
        this.personMobileNumber = personMobileNumber;
        this.sex = sex;
    }
    
    public Person(String personId, String personPwd, String userName, char sex, String personMobileNumber) {
        this.personId = personId;
        this.personPwd = personPwd;
        this.userName = userName;
        this.personMobileNumber = personMobileNumber;
        this.sex = sex;
    }
    
    public String getUserName() {
        return userName;
    }
    
    public void setUserName(String userName) {
        this.userName = userName;
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
    
    static boolean isPersonIdLegal(String pid){
        return pid.matches("^((Co)|(Wa)|(Bo)|(Cu))\\d{5}$");
    }
    static boolean isPersonPwdLegal(String pwd){
        // the default pwd is illegal  !!!attention
        String regex = "(?![^A-Za-z]+$)(?![^0-9]+$)[\\x21-\\x7e]{8,18}";//负向预查 检索不匹配全数字和全字母的串
        return pwd.matches(regex);
    }
    static boolean isPersonSexLegal(char sex) {
        return sex == 'F' || sex == 'M';
    }
    
    static boolean isPersonMobileNumberLegal(String MobileNumber) {
        if (null == MobileNumber) return false;
        String regex = "^1(([3-7]\\d)|(8[0-7]))\\d{4}0((3[1-9])|([4-6]\\d)|7[01])([01])$";
        return MobileNumber.matches(regex);
    }
    
    static boolean isPersonMobileNumberLegal(String MobileNumber, char sex) {
        if (null == MobileNumber) return false;
        String regex = "^1(([3-7]\\d)|(8[0-7]))\\d{4}0((3[1-9])|([4-6]\\d)|7[01])" + ((sex == 'M') ? "(0)$" : "(1)$");
        return MobileNumber.matches(regex);
    }
    
    public String toString() {
        return String.format("Name:%s\nSex:%c\nPhone:%s", this.userName, this.sex, this.personMobileNumber);
    }
    
    static Person addPerson(String name, char sex, String userMobileNumber) {
        if (isPersonSexLegal(sex) && isPersonMobileNumberLegal(userMobileNumber) && null != name) {
            return new Person(name, sex, userMobileNumber);
        } else return null;
    }
    
}
