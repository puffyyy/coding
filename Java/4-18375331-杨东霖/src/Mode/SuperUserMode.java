package Mode;

import entity.*;
import util.judge;

import java.util.ArrayList;
import java.util.Locale;
import java.util.Scanner;

public class SuperUserMode {
    public SuperUserMode() {
    }
    
    public void sudoMode(Scanner scanner) {
        System.out.println("Enter sudo mode");
        String readString;
        do {
            readString = scanner.nextLine().trim();
        } while (parseCommand(readString));
    }
    
    private boolean parseCommand(String line) {
        String[] arg = line.trim().split("\\s+");
        switch (arg[0]) {
            case "pp":
                parse_printPersonList(arg);
                break;
            case "sncu":
                parse_newCustomer(arg);
                break;
            case "snwa":
                parse_newWaiter(arg);
                break;
            case "snco":
                parse_newCook(arg);
                break;
            case "dcu":
                parse_delCustomer(arg);
                break;
            case "dwa":
                parse_delWaiter(arg);
                break;
            case "dco":
                parse_delCook(arg);
                break;
            case "SQ":
                return parse_quit(arg);
            case "":
                break;
            default:
                System.out.println("Call sudo method illegal");
        }
        return true;
    }
    
    private boolean parse_quit(String[] arg) {
        System.out.println(arg.length == 1 ? "Quit sudo mode" : "Params' count illegal");
        return arg.length != 1; //length not 1 -> true  length = 1 -> false ->quit
    }
    
    private void parse_newCook(String[] arg) {
        String output = judgeNew_(arg, PersonType.Cook);
        if (output.equals("Add new " + PersonType.Cook.toString().toLowerCase(Locale.ROOT) + " success")) {
            Cook.addPerson(arg[4], arg[1], arg[2].charAt(0), arg[3]);
        }
        System.out.println(output);
    }
    
    private void parse_newWaiter(String[] arg) {
        String output = judgeNew_(arg, PersonType.Waiter);
        if (output.equals("Add new " + PersonType.Waiter.toString().toLowerCase(Locale.ROOT) + " success")) {
            Waiter.addPerson(arg[4], arg[1], arg[2].charAt(0), arg[3]);
        }
        System.out.println(output);
    }
    
    private void parse_newCustomer(String[] arg) {
        String output = judgeNew_(arg, PersonType.Customer);
        if (output.equals("Add new " + PersonType.Customer.toString().toLowerCase(Locale.ROOT) + " success")) {
            Customer.addPerson(arg[4], arg[1], arg[2].charAt(0), arg[3]);
        }
        System.out.println(output);
    }
    
    private void parse_delCook(String[] arg) {
        String output = judgeDel_(arg, PersonType.Cook);
        if (output.equals("Delete " + PersonType.Cook.toString().toLowerCase(Locale.ROOT) + " success")) {
            PersonList.getInstance().delPerson(arg[1]);
        }
        System.out.println(output);
    }
    
    private void parse_delWaiter(String[] arg) {
        String output = judgeDel_(arg, PersonType.Waiter);
        if (output.equals("Delete " + PersonType.Waiter.toString().toLowerCase(Locale.ROOT) + " success")) {
            PersonList.getInstance().delPerson(arg[1]);
        }
        System.out.println(output);
    }
    
    private void parse_delCustomer(String[] arg) {
        String output = judgeDel_(arg, PersonType.Customer);
        if (output.equals("Delete " + PersonType.Customer.toString().toLowerCase(Locale.ROOT) + " success")) {
            PersonList.getInstance().delPerson(arg[1]);
        }
        System.out.println(output);
    }
    
    private void parse_printPersonList(String[] arg) {
        if (arg.length == 1) {
            ArrayList<Person> arr = PersonList.getInstance().getCurAllUserMap();
            if (0 == arr.size()) {
                System.out.println("Empty person list");
            } else {
                String format;
                int bound = arr.size();
                for (int i = 0; i < bound; i++) {
                    format = String.format("%d.%s", i + 1, arr.get(i).toStringPro());
                    System.out.println(format);
                }
            }
        } else System.out.println("Params' count illegal");
    }
    
    private String judgeNew_(String[] arg, PersonType type) {
        if (arg.length == 5) {
            if (arg[2].length() == 1 && judge.isPersonSexLegal(arg[2].charAt(0))) {
                if (judge.isPersonMobileNumberLegal(arg[3])) {
                    if (judge.isPersonMobileNumberLegal(arg[3], arg[2].charAt(0))) {
                        if (!PersonList.getInstance().isPersonExistedByMobileNumber(arg[3])) {
                            if (judge.isPersonIdLegal(arg[4], type)) {
                                if (!PersonList.getInstance().isPersonExistedByID(arg[4])) {
                                    return "Add new " + type.toString().toLowerCase(Locale.ROOT) + " success";
                                } else return type.toString() + " PID exists";
                            } else return type.toString() + " PID illegal";
                        } else return "Phone number exists";
                    } else return "Phone number doesn't match sex";
                } else return "Phone number illegal";
            } else return "Sex illegal";
        } else return "Params' count illegal";
    }
    
    private String judgeDel_(String[] arg, PersonType type) {
        if (arg.length == 2) {
            if (judge.isPersonIdLegal(arg[1], type)) {
                if (PersonList.getInstance().isPersonExistedByID(arg[1])) {
                    return "Delete " + type.toString().toLowerCase(Locale.ROOT) + " success";
                } else return "D-" + type.toString() + " PID doesn't exist";
            } else return "D-" + type.toString() + " PID illegal";
        } else return "Params' count illegal";
    }
}
