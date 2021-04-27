import Mode.PageBreakPrintMode;
import Mode.SuperUserMode;
import Mode.UserLoginMode;
import entity.Dish;
import entity.Menu;
import entity.Person;
import entity.PersonList;
import util.judge;

import java.util.ArrayList;

public class ParsingTerminal {
    //ParsingMenu refactor
    //public static entity.Menu menu;
    public ParsingTerminal() {
    }
    
    public static boolean parseCommand(String line, Menu menu) {
        String[] arg = line.trim().split("\\s+");
        switch (arg[0]) {
            case "SUDO":
                parse_superUserMode(arg);
                break;
            case "login":
                parse_login(arg);
                break;
            case "np":
                parse_np(arg);
                break;
            case "gd":
                parse_gd(arg, menu);
                break;
            case "udd":
                parse_udd(arg, menu);
                break;
            case "nd":
                parse_nd(arg, menu);
                break;
            case "pm":
                parse_pm(arg, menu);
                break;
            case "QUIT":
                return parse_quit(arg);
            case "":
                break;
            default:
                System.out.println("Command not exist");
        }
        return true;
    }
    
    private static void parse_login(String[] arg) {
        PersonList personList = PersonList.getInstance();
        if (arg.length >= 2 && (arg[1].equals("-i") || arg[1].equals("-n"))) {
            if (arg.length == 4) {
                if (arg[1].equals("-i")) {
                    if (judge.isPersonIdLegal(arg[2])) {
                        if (personList.isPersonExistedByID(arg[2])) {
                            Person p = personList.getPersonById(arg[2]);
                            if (p.checkPersonPwd(arg[3])) {
                                UserLoginMode userLoginMode = new UserLoginMode(p);
                                userLoginMode.loginMode(Test.scanner);
                            } else System.out.println("Password not match");
                        } else System.out.println("Pid not exist");
                    } else System.out.println("PID illegal");
                } else //if (arg[3].equals("-n"))
                {
                    if (judge.isPersonNameLegal(arg[2])) {
                        if (personList.isPersonExistedByName(arg[2])) {
                            Person p = personList.getPersonByName(arg[2]);
                            if (p.checkPersonPwd(arg[3])) {
                                UserLoginMode userLoginMode = new UserLoginMode(p);
                                userLoginMode.loginMode(Test.scanner);
                            } else System.out.println("Password not match");
                        } else System.out.println("Pname not exist");
                    } else System.out.println("Pname illegal");
                }
            } else System.out.println("Params' count illegal");
        } else System.out.println("Command not exist");
    }
    
    private static void parse_superUserMode(String[] arg) {
        if (arg.length == 1) {
            SuperUserMode superUserMode = new SuperUserMode();
            superUserMode.sudoMode(Test.scanner);
        } else System.out.println("Params' count illegal");
    }
    
    public static boolean parse_quit(String[] arg) {
        if (arg.length == 1) {
            System.out.println("----- Good Bye! -----");
            System.exit(0);
        } else System.out.println("Params' count illegal");
        return true;
    }
    
    private static void parse_np(String[] arguments) {
        if ((arguments.length == 4)) {
            if (arguments[2].length() == 1 && judge.isPersonSexLegal(arguments[2].charAt(0))) {
                if (judge.isPersonMobileNumberLegal(arguments[3], arguments[2].charAt(0))) {
                    Person user = Person.addPerson(arguments[1], arguments[2].charAt(0), arguments[3]);
                    System.out.println(user);
                } else System.out.println("Phone number illegal");
            } else System.out.println("Sex illegal");
        } else System.out.println("Params' count illegal");
    }
    
    /**
     * @param arguments udd -? id ***
     */
    private static void parse_udd(String[] arguments, Menu menu) {
        if (arguments.length >= 2 && (arguments[1].equals("-t") || arguments[1].equals("-p") || arguments[1].equals("-n"))) {
            if (arguments.length == 4) {
                if (judge.isDishIdLegal(arguments[2])) {//judge did legal
                    if (menu.isDishExistById(arguments[2])) {
                        switch (arguments[1]) {
                            case "-n":
                                int state = menu.updateDish(arguments[2], arguments[3]);
                                if (state == 1) System.out.println("Update dish's name success");
                                else if (state == -1) System.out.println("New name input illegal");
                                else if (state == -2) System.out.println("New name repeated");
                                break;
                            case "-t":
                                if (judge.isInteger(arguments[3]) && menu.updateDish(arguments[2], Integer.parseInt(arguments[3])))
                                    System.out.println("Update dish's total success");
                                else System.out.println("Change dish's total illegal");
                                break;
                            case "-p":
                                if (judge.isDouble(arguments[3]) && menu.updateDish(arguments[2], Double.parseDouble(arguments[3])))
                                    System.out.println("Update dish's price success");
                                else System.out.println("Change dish's price illegal");
                                break;
                        }
                    } else System.out.println("Dish does not exist");
                } else System.out.println("Did input illegal");
            } else System.out.println("Params' count illegal");
        } else System.out.println("Command not exist");
    }
    
    private static void parse_nd(String[] arguments, Menu menu) {
        double price;
        int total;
        if (arguments.length == 5) {
            if (judge.isDishIdLegal(arguments[1])) {
                if (!menu.isDishExistById(arguments[1])) {
                    if (judge.isDouble(arguments[3]) && judge.isInteger(arguments[4])) {//convert format
                        price = Double.parseDouble(arguments[3]);
                        total = Integer.parseInt(arguments[4]);
                        int state = menu.newDishAdd(arguments[1], arguments[2], price, total);//judge all the attributes
                        if (state == 1) System.out.println("Add dish success");
                        else if (state == -1) System.out.println("New dish's attributes input illegal");
                        else if (state == -2) System.out.println("Name repeated");
                    } else System.out.println("New dish's attributes input illegal");
                } else System.out.println("Dish exists");
            } else System.out.println("Did input illegal");
        } else System.out.println("Params' count illegal");
    }
    
    private static void parse_pm(String[] arguments, Menu menu) {
        ArrayList<Dish> dishList = menu.getAllDishList();
        if (arguments.length == 1) {
            if (dishList.size() <= 0) System.out.println("Empty Menu");
            String format;
            int bound = dishList.size();
            for (int i = 0; i < bound; i++) {
                format = String.format("%d. %s", i + 1, dishList.get(i));
                System.out.println(format);
            }
        } else if (arguments.length == 3) {
            if (judge.isInteger(arguments[1]) && judge.isPositiveInteger(arguments[2])) {
                if (dishList.size() <= 0)
                    System.out.println("Menu is empty, exit page check mode");
                else {
                    int n = Integer.parseInt(arguments[1]);//n页
                    int m = Integer.parseInt(arguments[2]);//m个
                    PageBreakPrintMode pagePrinting = new PageBreakPrintMode(dishList, n, m);
                    pagePrinting.innerPageBreakMode(Test.scanner);
                }
            } else System.out.println("Page slice method's params input illegal");//oms2 test ultimate can not access
        } else System.out.println("Params' count illegal");
    }
    
    private static void parse_gd(String[] arguments, Menu menu) {
        if (arguments.length >= 2) {
            // function search id
            if (arguments[1].equals("-id")) {
                if (arguments.length == 3) {
                    if (judge.isDishIdLegal(arguments[2])) {
                        Dish getDish = menu.getDishById(arguments[2]);
                        if (getDish != null) System.out.println(getDish);
                        else System.out.println("Dish does not exist");
                    } else System.out.println("Did input illegal");
                } else System.out.println("Params' count illegal");
            }
            // function search keyword
            else if (arguments[1].equals("-key")) {
                //print all
                if (arguments.length == 3) {
                    ArrayList<Dish> dishArr = menu.getDishByKeyWord(arguments[2]);
                    if (dishArr.isEmpty())
                        System.out.println("Dish does not exist");
                    else {
                        String format;
                        int bound = dishArr.size();
                        for (int i = 0; i < bound; i++) {
                            format = String.format("%d. %s", i + 1, dishArr.get(i));
                            System.out.println(format);
                        }
                    }
                }
                //print page break
                else if (arguments.length == 5) {
                    ArrayList<Dish> dishList = menu.getDishByKeyWord(arguments[2]);
                    if (dishList.isEmpty())
                        System.out.println("Dish does not exist");
                    else if (judge.isInteger(arguments[3]) && judge.isPositiveInteger(arguments[4])) {
                        int n = Integer.parseInt(arguments[3]);//n页
                        int m = Integer.parseInt(arguments[4]);//m个
                        PageBreakPrintMode pagePrinting = new PageBreakPrintMode(dishList, n, m);
                        pagePrinting.innerPageBreakMode(Test.scanner);
                    } else System.out.println("Page slice method's params input illegal");
                } else System.out.println("Params' count illegal");
            } else System.out.println("Command not exist");
        } else System.out.println("Command not exist");
        
    }
    
}

