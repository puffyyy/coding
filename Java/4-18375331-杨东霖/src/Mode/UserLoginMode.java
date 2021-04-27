package Mode;

import entity.Customer;
import entity.Person;
import util.judge;

import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class UserLoginMode {
    Person loginPerson;
    
    public UserLoginMode(Person loginPerson) {
        this.loginPerson = loginPerson;
    }
    
    public void loginMode(Scanner scanner) {
        System.out.println("Login success");
        String readString;
        do {
            readString = scanner.nextLine().trim();
        } while (parseCommand(readString));
    }
    
    private boolean parseCommand(String line) {
        String[] arg = line.trim().split("\\s+");
        boolean parsed = false;
        switch (loginPerson.getPersonType()) {
            case Customer:
                parsed = CustomerMode.parse_customerMethod(arg, loginPerson);
                break;
            case Cook:
                
                break;
            case Waiter:
                
                break;
        }
        if (!parsed)
            switch (arg[0]) {
                case "myinfo":
                    parse_info(arg);
                    break;
                case "back":
                    parse_back(arg);
                    return false;
                case "QUIT":
                    parse_quit(arg);
                    return false;//duplicate
                case "chgpw":
                    parse_chgpw(arg);
                    break;
                case "":
                    break;
                default:
                    System.out.println("Command not exist");
            }
        return true;
    }
    
    private void parse_chgpw(String[] arg) {
        if (arg.length == 3) {
            if (judge.isPersonPwdLegal(arg[1])) {
                if (arg[1].equals(arg[2])) {
                    loginPerson.setPersonPwd(arg[1]);
                    System.out.println("Change password success");
                } else System.out.println("Not match");
            } else System.out.println("New password illegal");
        } else System.out.println("Params' count illegal");
    }
    
    private void parse_back(String[] arg) {
        System.out.println(arg.length == 1 ? "Logout success" : "Params' count illegal");
    }
    
    private void parse_info(String[] arg) {
        if (arg.length == 1) {
            String format = String.format("[info]\n" +
                            "| name:\t%s\n" +
                            "| Sex:\t%c\n" +
                            "| Pho:\t%s\n" +
                            "| PID:\t%s\n" +
                            "| Pwd:\t%s\n" +
                            "| Type:\t%s"
                    , loginPerson.getPersonName(), loginPerson.getSex()
                    , loginPerson.getPersonMobileNumber(), loginPerson.getPersonId()
                    , loginPerson.getPersonPwd(), loginPerson.getPersonType());
            System.out.println(format);
        } else System.out.println("Params' count illegal");
    }
    
    private void parse_quit(String[] arg) {
        if (arg.length == 1) {
            System.out.println("----- Good Bye! -----");
            System.exit(0);
        } else System.out.println("Params' count illegal");
    }
    
    static class CustomerMode {
        static List<String> customerMethodList = Arrays.asList("rc", "gb", "aplVIP");
        static Customer customer;
        
        public static boolean parse_customerMethod(String[] arg, Person customer) {
            CustomerMode.customer = (Customer) customer;
            int index = customerMethodList.indexOf(arg[0]);
            if (index == -1) return false;
            else {
                switch (index) {
                    case 0:
                        parse_rc(arg);
                        break;
                    case 1:
                        parse_gb(arg);
                        break;
                    case 2:
                        parse_aplVIP(arg);
                        break;
                }
            }
            return true;
        }
        
        private static void parse_aplVIP(String[] arg) {
            if (arg.length == 1) {
                if (customer.isApplyVIPSuccess()) {
                    System.out.println("Apply VIP success");
                } else System.out.println("Please recharge more");
            } else System.out.println("Params' count illegal");
        }
        
        private static void parse_gb(String[] arg) {
            if (arg.length == 1) {
                System.out.println("Balance: " + customer.getAccountBalance());
            } else System.out.println("Params' count illegal");
        }
        
        private static void parse_rc(String[] arg) {
            if (arg.length == 2) {
                if (judge.isDouble(arg[1])) {
                    double amount = Double.parseDouble(arg[1]);
                    if (amount >= 100 && amount < 1000) customer.recharge(amount);
                    else System.out.println("Recharge input illegal");
                } else System.out.println("Recharge input illegal");
            } else System.out.println("Params' count illegal");
        }
    }
}
